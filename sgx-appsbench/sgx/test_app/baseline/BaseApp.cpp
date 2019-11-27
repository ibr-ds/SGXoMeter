//
// Created by moe on 17.07.19.
//

#include "BaseApp.h"
#include "BenchThread.h"
#include "GlobalVariables.h"

#ifdef RUNTIME_PARSER
#include "InputParser.h"
#endif


/*  SIGINT handler in order to stop the benchmark with Ctrl+C   */
void InterruptHandler(int dummy)
{
    (void)dummy;
    stop_bench();
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
    __sync_fetch_and_and(&counter,((uint64_t)0)); // reset the counter for the possible next warmup phase
    while(do_bench == 0)
    {
        __asm__("pause");
    }

    doWarmUp();                                   // do the warm up phase and store its result in the array
    doRuntime();                                  // do the runtime phase and store its result in the array
    pause_bench();                                // pause the Benchmark to stop incrementing the counter
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
    run_bench(test_id);
    return nullptr;
}

#define BASELINE_DATA_FILENAME  "BaselineData.txt"
static void print_array()
{
    //ToDo do the format of the output file
#ifdef WRITE_LOG_FILE
    FILE *fp;
    fp = fopen(BASELINE_DATA_FILENAME, "a");
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
    fprintf(stderr, "Results are saved in a text file with the name: %s\n", BASELINE_DATA_FILENAME);
    fclose(fp);
#endif
}


static void run_tests()
{
    for (int test_id = 1; test_id < NUM_OF_TEST_MODULES+DUMMY_INDEX; ++test_id)
    {
        abort_measure = 0;
        pthread_t measure, worker[WORKER_THREADS];
        pthread_create(&measure, nullptr, measure_thread, nullptr); // start the measure thread
        pthread_barrier_init(&worker_barrier, nullptr, WORKER_THREADS + 1);
        for (int j = 0; j < (int)WORKER_THREADS; ++j)
        {
            //ToDo danger: i didnt pass by value because we only have 1 worker thread and its okay in this case but
            // if multiple threads then its better to pass by value as thread creation and execution may differ
            pthread_create(worker+j, nullptr, worker_thread, &test_id);
        }
        pthread_barrier_wait(&worker_barrier);

        fprintf(stderr, "Starting to benchmark the Module %s \n", test_names[test_id]);
        counter = 0;
        start_bench();
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
    set_config((uint64_t *)&counter, &GLOBAL_CONFIG);

    // Run the benchmarks for each chosen test
    run_tests();

    // Print the array to an output file with some statistics information. For example, the rate of the executed tests per seconds
    print_array();
}

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

    signal(SIGINT, InterruptHandler);

    /* Initialize the enclave and execute the benchmarking setup */
    exec_bench_setup();

    return 0;
}
