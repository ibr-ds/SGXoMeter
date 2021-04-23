//
// Created by moe on 17.07.19.
//

#ifndef SGX_APPSBENCH_BENCHTHREAD_H
#define SGX_APPSBENCH_BENCHTHREAD_H


#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#include "UtilsStructs.h"

#if defined(__cplusplus)
extern "C" {
#endif


void start_bench(void);
void pause_bench(void);
void stop_bench(void);
#ifndef INCLUDE_TRANSITIONS
void run_bench(int test_id, int thread_id);
#else
void run_bench_with_transitions(int test_id, int thread_id);
#endif
void set_config(uint64_t **ctr, void *globalConfig);
void cleanup_bench(void);

/*
 * This includes the function signatures of the chosen modules
 */
#include "testFunctionsSignatures.h"

#if defined(__cplusplus)
}
#endif


#endif //SGX_APPSBENCH_BENCHTHREAD_H
