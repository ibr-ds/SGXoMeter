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


#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <unistd.h>
#include <pwd.h>
#include <libgen.h>
#include <stdlib.h>
#include <pthread.h>

# define MAX_PATH FILENAME_MAX


#include <sgx_urts.h>
#include <csignal>

#include "TestApp.h"

#include "TestEnclave_u.h"



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
                printf("Info: %s\n", sgx_errlist[idx].sug);
            printf("Error: %s\n", sgx_errlist[idx].msg);
            break;
        }
    }
    
    if (idx == ttl)
        printf("Error: Unexpected error occurred [0x%x].\n", ret);
}

void print_ret_error(sgx_status_t ret) {
    if (ret != SGX_SUCCESS)
    {
        fprintf(stderr, "SGX error: 0x%x\n", ret);
        exit(-1);
    }
}

/* Initialize the enclave:
 *   Step 1: retrive the launch token saved by last transaction
 *   Step 2: call sgx_create_enclave to initialize an enclave instance
 *   Step 3: save the launch token if it is updated
 */
int initialize_enclave(void)
{
    char token_path[MAX_PATH] = {'\0'};
    sgx_launch_token_t token = {0};
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int updated = 0;
    /* Step 1: retrive the launch token saved by last transaction */

    /* try to get the token saved in $HOME */
    const char *home_dir = getpwuid(getuid())->pw_dir;
    if (home_dir != NULL && 
        (strlen(home_dir)+strlen("/")+sizeof(TOKEN_FILENAME)+1) <= MAX_PATH) {
        /* compose the token path */
        strncpy(token_path, home_dir, strlen(home_dir));
        strncat(token_path, "/", strlen("/"));
        strncat(token_path, TOKEN_FILENAME, sizeof(TOKEN_FILENAME)+1);
    } else {
        /* if token path is too long or $HOME is NULL */
        strncpy(token_path, TOKEN_FILENAME, sizeof(TOKEN_FILENAME));
    }

    FILE *fp = fopen(token_path, "rb");
    if (fp == NULL && (fp = fopen(token_path, "wb")) == NULL) {
        printf("Warning: Failed to create/open the launch token file \"%s\".\n", token_path);
    }
    printf("token_path: %s\n", token_path);
    if (fp != NULL) {
        /* read the token from saved file */
        size_t read_num = fread(token, 1, sizeof(sgx_launch_token_t), fp);
        if (read_num != 0 && read_num != sizeof(sgx_launch_token_t)) {
            /* if token is invalid, clear the buffer */
            memset(&token, 0x0, sizeof(sgx_launch_token_t));
            printf("Warning: Invalid launch token read from \"%s\".\n", token_path);
        }
    }

    /* Step 2: call sgx_create_enclave to initialize an enclave instance */
    /* Debug Support: set 2nd parameter to 1 */

    ret = sgx_create_enclave(TESTENCLAVE_FILENAME, SGX_DEBUG_FLAG, &token, &updated, &global_eid, NULL);

    if (ret != SGX_SUCCESS) {
        print_error_message(ret);
        printf("something LOOOOOOOOONG");
        if (fp != NULL) fclose(fp);

        return -1;
    }

    /* Step 3: save the launch token if it is updated */

    if (updated == FALSE || fp == NULL) {
        /* if the token is not updated, or file handler is invalid, do not perform saving */
        if (fp != NULL) fclose(fp);
        return 0;
    }

    /* reopen the file with write capablity */
    fp = freopen(token_path, "wb", fp);
    if (fp == NULL) return 0;
    size_t write_num = fwrite(token, 1, sizeof(sgx_launch_token_t), fp);
    if (write_num != sizeof(sgx_launch_token_t))
        printf("Warning: Failed to save launch token to \"%s\".\n", token_path);
    fclose(fp);

    return 0;
}

static volatile int do_bench = 0;
static volatile int abort_measure = 0;
volatile uint64_t counter = 0;
uint64_t RATE = 100000;

static inline uint64_t rdtscp( uint32_t & aux )
{
    uint64_t rax,rdx;
    asm volatile ( "rdtscp\n" : "=a" (rax), "=d" (rdx), "=c" (aux) : : );
    return (rdx << 32) + rax;
}

typedef struct {
    uint64_t tsc;
    uint64_t diff;
} measurement_t;

measurement_t *array;
#define ARRAY_SIZE (1000000)
uint64_t cur_elem = 0;
uint32_t a;


static inline void add_measurement(uint64_t diff)
{
    array[cur_elem].diff = diff;
    array[cur_elem].tsc = rdtscp(a);
    ++cur_elem;
    if (cur_elem >= ARRAY_SIZE)
        cur_elem = 0;
}

// "print" to array

void *measure_thread(void *args)
{
    printf("# RATE: %lu µs\n", RATE);
    uint64_t last = 0, diff;
    uint64_t next = 0;
    while(do_bench == 0)
    {
        __asm__("pause");
    }
    while(abort_measure == 0)
    {
        next = rdtscp(a) + RATE;
        diff = counter - last;
        last = counter;
        add_measurement(diff);
        while(rdtscp(a) < next)
        {
            __asm__("pause");
        }
    }

    return nullptr;
}

uint64_t WORKER_THREADS = 1; //ToDo this should probably be 2 not 1
pthread_barrier_t worker_barrier;

void *worker_thread(void *args)
{
    pthread_barrier_wait(&worker_barrier);
    while(do_bench == 0)
    {
        __asm__("pause");
    }
    sgx_status_t ret = ecall_run_bench(global_eid);
    print_ret_error(ret);
    return nullptr;
}

static void print_array()
{
    // print array
    uint64_t end = cur_elem - 1;
    if (end < 0)
    {
        end = ARRAY_SIZE - 1;
    }
    uint64_t prev_elem = end;
    uint64_t start_tsc = 0;
    while (cur_elem != end)
    {
        if (array[cur_elem].tsc != 0)
        {
            if (start_tsc == 0)
                start_tsc = array[cur_elem].tsc;

            printf("%lu, %lu, %lu\n", array[cur_elem].tsc - start_tsc, array[cur_elem].diff, array[cur_elem].tsc - array[prev_elem].tsc);
        }
        ++cur_elem;
        ++prev_elem;
        if (cur_elem >= ARRAY_SIZE)
        {
            cur_elem = 0;
        }
        if (prev_elem >= ARRAY_SIZE)
        {
            prev_elem = 0;
        }
    }
}

static void exec_bench_setup(int iterNr)
{
    sgx_status_t ret = SGX_SUCCESS;

    /* Initialize the enclave */
    if (initialize_enclave() != 0)
    {
        printf("Enclave Initialization Error\n");
        return;
    }

    pthread_t measure, worker[WORKER_THREADS];
    pthread_create(&measure, nullptr, measure_thread, nullptr); // start the measure thread
    pthread_barrier_init(&worker_barrier, nullptr, WORKER_THREADS + 1);
    for (int i = 0; i < WORKER_THREADS; ++i)
    {
        pthread_create(worker+i, nullptr, worker_thread, nullptr);
    }
    pthread_barrier_wait(&worker_barrier);

    fprintf(stderr, "Starting benchmark \n");
    counter = 0;
    array = (measurement_t *)calloc(ARRAY_SIZE, sizeof(measurement_t));
    ret = ecall_start_bench(global_eid, (uint64_t *)&counter, iterNr);
    print_ret_error(ret);
    do_bench = 1;


    for (int i = 0; i < WORKER_THREADS; ++i)
    {
        fprintf(stderr, "Joining worker %d\n", i);
        pthread_join(worker[i], nullptr);
    }
    sgx_destroy_enclave(global_eid);

    abort_measure = 1;
    fprintf(stderr, "Joining measure \n");
    pthread_join(measure, nullptr);

    print_array();
}

/*  SIGINT handler in order to stop the benchmark with Ctrl+C   */
void intHandler(int dummy)
{
    (void)dummy;
    sgx_status_t ret = SGX_SUCCESS;
    ret = ecall_stop_bench(global_eid);
    print_ret_error(ret);
}

/*  provide the number of the wanted benchmark iterations       */
int get_num_of_iterations()
{
    int iterNr=0;
    printf("Please insert the desired number of iterations?\n ");
    int result = scanf("%d", &iterNr);

    if (result == EOF)
    {
        printf("stdin ERROR while reading!\n Number of iteration is set to unlimited\n");
    }
    if (result == 0) //in case of invalid input like out of context string or anything rather than an int
    {
        while (fgetc(stdin) != '\n') // Read until a newline is found
            ;
        printf("nothing or invalid input is read!.\n");
    }
    if(iterNr > 0)
    {
        printf("The benchmark will run with %d iterations!\n", iterNr);
    } else {
        printf("The benchmark will run indefinitely!.Therefore, please consider pressing 'Ctrl+C' in order to stop the benchmark\n");
    }
    fflush(stdout);
    return iterNr;
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


/* Application entry */
int main(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    signal(SIGINT, intHandler);


    int iterNr = get_num_of_iterations();

    /* Initialize the enclave and execute the benchmarking setup */
    exec_bench_setup(iterNr);

    return 0;
}
