//
// Created by moe on 01.10.19.
//

#ifndef SGX_APPSBENCH_MEASUREMENTUTILS_H
#define SGX_APPSBENCH_MEASUREMENTUTILS_H

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define timeNow() std::chrono::high_resolution_clock::now()
#define duration(a) std::chrono::duration_cast<std::chrono::seconds>(a).count()

#define PAUSED    0
#define RUNNING   1
#define STOPED    2

static volatile int do_bench = 0;
static volatile int abort_measure = 0;
volatile uint64_t *counter = NULL;
uint64_t tmpCounter = 0;


typedef struct {
    uint64_t warmCnt;
    uint64_t runCnt;
    uint64_t totalRuntime;
} measurement_t;


measurement_t array[NUM_OF_TEST_MODULES];
uint64_t cur_elem = 0;

static inline void add_warm_measurement()
{
    uint64_t total_throughput = 0;
    for (int i = 0; i < GLOBAL_CONFIG.NUM_OF_WTHREADS; ++i) {
        total_throughput += counter[i];
    }
    tmpCounter = array[cur_elem].warmCnt = total_throughput;
}


static inline void add_runtime_measurement(uint64_t totalRuntime)
{
    uint64_t total_throughput = 0;
    for (int i = 0; i < GLOBAL_CONFIG.NUM_OF_WTHREADS; ++i) {
        total_throughput += counter[i];
    }
    array[cur_elem].runCnt = (total_throughput - tmpCounter);
    array[cur_elem].totalRuntime = totalRuntime;
    ++cur_elem;                                                     // next element in the array for the next test
}

void doWarmUp()
{
    TimeVar initTime = timeNow();
    TimeVar currentTime;
    do
    {
        __asm__("pause");
        currentTime = timeNow();
    } while(abort_measure == 0 && duration(currentTime - initTime) <  GLOBAL_CONFIG.WARMUP_TIME);
    add_warm_measurement();                                         // add the warmup results
}

void doRuntime()
{
    TimeVar initTime = timeNow();
    TimeVar curTime = timeNow();
    if(GLOBAL_CONFIG.NUM_OF_ITERATION > 0)                          // in case measuring the time for specific number of iterations
    {
        uint64_t runTimeCounter = 0;
        do{
            __asm__("pause");
            uint64_t total_throughput = 0;
            for (int i = 0; i < GLOBAL_CONFIG.NUM_OF_WTHREADS; ++i) {
                total_throughput += counter[i];
            }
            runTimeCounter = total_throughput - tmpCounter;
            curTime = timeNow();
        } while (abort_measure == 0 && runTimeCounter < GLOBAL_CONFIG.NUM_OF_ITERATION);
    } else {                                                        // in case measuring the number of iteration for a specific runtime
        while(abort_measure == 0 && duration(curTime - initTime) < GLOBAL_CONFIG.RUNTIME)
        {
            __asm__("pause");
            curTime = timeNow();
        }
    }
    add_runtime_measurement(duration(curTime - initTime));       // add the runtime results, reset the tests counter and increment the pointer to the next test
}

#endif //SGX_APPSBENCH_MEASUREMENTUTILS_H