/*
 * Copyright (C) 2011-2017 Intel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of Intel Corporation nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "TestApp.h"
#include "TestEnclave_u.h"


# define MAX_PATH FILENAME_MAX

#include "GlobalVariables.h"

#ifdef RUNTIME_PARSER
#include "InputParser.h"
#endif

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

typedef struct _sgx_errlist_t {
    sgx_status_t err;
    const char *msg;
    const char *sug; /* Suggestion */
} sgx_errlist_t;

/* Error code returned by sgx_create_enclave */
static sgx_errlist_t sgx_errlist[] = {
    {
        SGX_ERROR_UNEXPECTED,
        "Unexpected error occurred.",
        NULL
    },
    {
        SGX_ERROR_INVALID_PARAMETER,
        "Invalid parameter.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_MEMORY,
        "Out of memory.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_LOST,
        "Power transition occurred.",
        "Please refer to the sample \"PowerTransition\" for details."
    },
    {
        SGX_ERROR_INVALID_ENCLAVE,
        "Invalid enclave image.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ENCLAVE_ID,
        "Invalid enclave identification.",
        NULL
    },
    {
        SGX_ERROR_INVALID_SIGNATURE,
        "Invalid enclave signature.",
        NULL
    },
    {
        SGX_ERROR_OUT_OF_EPC,
        "Out of EPC memory.",
        NULL
    },
    {
        SGX_ERROR_NO_DEVICE,
        "Invalid Intel® Software Guard Extensions device.",
        "Please make sure Intel® Software Guard Extensions module is enabled in the BIOS, and install Intel® Software Guard Extensions driver afterwards."
    },
    {
        SGX_ERROR_MEMORY_MAP_CONFLICT,
        "Memory map conflicted.",
        NULL
    },
    {
        SGX_ERROR_INVALID_METADATA,
        "Invalid enclave metadata.",
        NULL
    },
    {
        SGX_ERROR_DEVICE_BUSY,
        "Intel® Software Guard Extensions device was busy.",
        NULL
    },
    {
        SGX_ERROR_INVALID_VERSION,
        "Enclave version was invalid.",
        NULL
    },
    {
        SGX_ERROR_INVALID_ATTRIBUTE,
        "Enclave was not authorized.",
        NULL
    },
    {
        SGX_ERROR_ENCLAVE_FILE_ACCESS,
        "Can't open enclave file.",
        NULL
    },
};

/* Check error conditions for loading enclave */
void print_error_message(sgx_status_t ret)
{
    size_t idx = 0;
    size_t ttl = sizeof sgx_errlist/sizeof sgx_errlist[0];

    for (idx = 0; idx < ttl; idx++) {
        if(ret == sgx_errlist[idx].err) {
            if(NULL != sgx_errlist[idx].sug)
                fprintf(stderr, "Info: %s\n", sgx_errlist[idx].sug);
            fprintf(stderr, "Error: %s\n", sgx_errlist[idx].msg);
            break;
        }
    }
    
    if (idx == ttl)
        printf("Error: Unexpected error occurred [0x%x].\n", ret);
}

void print_ret_error(sgx_status_t ret) {
    if (ret != SGX_SUCCESS)
    {
        fprintf(stderr, "SGX error: 0x%x\n", ret); //ToDo probably remove this as it's not important anymore
        print_error_message(ret);
        exit(-1);
    }
}

/* Initialize the enclave:
 *
 *  call sgx_create_enclave to initialize an enclave instance and don't save the token inorder to avoid token conflict
 *
 */
int initialize_enclave(void)
{
    sgx_launch_token_t token = {0};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int updated = 0;

    ret = sgx_create_enclave(TESTENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);

    if (ret != SGX_SUCCESS)
    {
        print_error_message(ret);
        return -1;
    }
    return 0;
}


/*  SIGINT handler in order to stop the benchmark with Ctrl+C   */
void ecallInterruptHandler(int dummy)
{
    (void)dummy;
    sgx_status_t ret = SGX_SUCCESS;
    ret = ecall_stop_bench(global_eid);
    print_ret_error(ret);
}


/*
 * This includes an array of all chosen test modules
 */
#include "testNames.h"



/*
 * This includes the time measurement struct and the associated functions
 */
#include "measurementUtils.h"


void *measure_thread(void *args)
{
    __sync_fetch_and_and(&counter,((uint64_t)0));       // reset the counter for the possible next warmup phase
    while(do_bench == 0)
    {
        __asm__("pause");
    }

    doWarmUp();                                          // do the warm up phase and store its result in the array
    doRuntime();                                         // do the runtime phase and store its result in the array
    sgx_status_t ret = ecall_pause_bench(global_eid);   // pause the Benchmark to stop incrementing the counter
    print_ret_error(ret);
    return nullptr;
}

uint64_t WORKER_THREADS = 1;
pthread_barrier_t worker_barrier;

void *worker_thread(void *args)
{
    int *argptr = (int*) args;
    int test_id = *argptr;

    pthread_barrier_wait(&worker_barrier);  // register +1 to the thread barrier instance
    while(do_bench == 0)
    {
        __asm__("pause");
    }

    sgx_status_t ret = ecall_run_bench(global_eid, test_id);
    print_ret_error(ret);
    return nullptr;
}


static void print_array()
{
    //ToDo do the format of the output file
#ifdef WRITE_LOG_FILE
    FILE *fp;
    fp = fopen(GLOBAL_CONFIG.DATA_FILE_NAME, "a");
    if (fp == NULL)
    {
        fprintf(stderr, "Couldnt open or create a file for the plot data!\n");
    }
#endif

    /*
     * This includes the printing loop of the data in the measurement array
     */
    #include "arrayPrintLoop.h"

#ifdef WRITE_LOG_FILE
    fprintf(stderr, "Results are saved in a text file with the name: %s\n", GLOBAL_CONFIG.DATA_FILE_NAME);
    fclose(fp);
#endif
}


static void run_tests()
{
    for (int test_id = 1; test_id < NUM_OF_TEST_MODULES+DUMMY_INDEX; ++test_id)
    {
        //ToDo Maybe we should reset the counter just in case?! (Ask Nico)
        abort_measure = 0;
        sgx_status_t ret = SGX_SUCCESS;
        pthread_t measure, worker[WORKER_THREADS];
        pthread_create(&measure, nullptr, measure_thread, nullptr); // start the measure thread
        pthread_barrier_init(&worker_barrier, nullptr, WORKER_THREADS + 1);
        for (int j = 0; j < (int)WORKER_THREADS; ++j)
        {
            //ToDo danger: i didnt pass by value because we only have 1 worker thread and its okay in this case but
            // if multiple threads then its better to pass by value as thread creation and execution may differ
            pthread_create(&worker[j], nullptr, worker_thread, (void *)&test_id);
        }
        pthread_barrier_wait(&worker_barrier);

        fprintf(stderr, "Starting to benchmark the Module %s \n", test_names[test_id]);
        counter = 0;
        ret = ecall_start_bench(global_eid);
        print_ret_error(ret);
        do_bench = 1;


        for (int j = 0; j < (int)WORKER_THREADS; ++j)
        {
            fprintf(stderr, "Joining worker %d\n", j);
            pthread_join(worker[j], nullptr);
        }

        abort_measure = 1;
        fprintf(stderr, "Joining measure \n");
        pthread_join(measure, nullptr);
        do_bench = 0;
        pthread_barrier_destroy(&worker_barrier);
    }
}

static void exec_bench_setup()
{
    /*
     * enclave initialization should be done once
     */
    sgx_status_t ret = SGX_SUCCESS;

    /* Initialize the enclave */
    if (initialize_enclave() != 0)
    {
        printf("Enclave Initialization Error\n");
        return;
    }

    /*
     * Pass the global config variable and the counter to the enclave
     */
    ret = ecall_set_config(global_eid, (uint64_t *)&counter, &GLOBAL_CONFIG);
    print_ret_error(ret);

    // Run the benchmarks for each chosen test
    run_tests();

    // call the post benchmark functions for clean up
    ret = ecall_cleanup_bench(global_eid);
    print_ret_error(ret);

    // Destroy the enclave after all tests have been run and executed completely
    ret = sgx_destroy_enclave(global_eid);
    print_ret_error(ret);
    // Print the array to an output file with some statistics information. For example, the rate of the executed tests per seconds
    print_array();
}



/* OCall functions */
void uprint(const char *str)
{
    /* Proxy/Bridge will check the length and null-terminate 
     * the input string to prevent buffer overflow. 
     */
    printf("%s", str);
    fflush(stdout);
}


void usgx_exit(int reason)
{
	printf("usgx_exit: %d\n", reason);
	exit(reason);
}


void* thread_test_func(void* p)
{
	new_thread_func(global_eid);
	return NULL;
}

int ucreate_thread()
{
	pthread_t thread;
	int res = pthread_create(&thread, NULL, thread_test_func, NULL);
	return res;
}

#include "ocallDefinitions.h"

/*  ToDo: memset is used in seeq libraries, therefore i defined the two methods below just in case. However seeq seems to work without adding them, so maybe remove them if not needed?!   */
#ifdef MEMSET_SGX
void* memset_s(void* dest, size_t destsz, int c, size_t len) {
    return memset(dest, c, destsz < len ? destsz : len);
}

int consttime_memequal(const void *b1, const void *b2, size_t len)
{
    const unsigned char *c1 = static_cast<const unsigned char *>(b1), *c2 = static_cast<const unsigned char *>(b2);
    unsigned int res = 0;

    while (len--)
        res |= *c1++ ^ *c2++;

    /*
     * Map 0 to 1 and [1, 256) to 0 using only constant-time
     * arithmetic.
     *
     * This is not simply `!res' because although many CPUs support
     * branchless conditional moves and many compilers will take
     * advantage of them, certain compilers generate branches on
     * certain CPUs for `!res'.
     */
    return (1 & ((res - 1) >> 8));
}
#endif


/* Application entry */
int main(int argc, char *argv[])
{
#ifdef RUNTIME_PARSER
    parseInput(argc, argv);
#else
    (void)(argc);
    (void)(argv);
#endif

#ifdef PRINT_CHECKS
    fprintf(stderr, "# Warmup phase: %lus\n", GLOBAL_CONFIG.WARMUP_TIME);
    fprintf(stderr, "# Runtime phase: %lus\n", GLOBAL_CONFIG.RUNTIME);
#endif

    signal(SIGINT, ecallInterruptHandler);

    /* Initialize the enclave and execute the benchmarking setup */
    exec_bench_setup();

    return 0;
}
