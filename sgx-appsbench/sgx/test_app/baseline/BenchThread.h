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
void run_bench(int test_id);
void set_config(uint64_t *ctr, void *globalConfig);


#ifdef RSA_TESTS
int rsa_test();
#endif
#ifdef ELLIPTIC_CURVE_TESTS
int ec_test();
#endif
#ifdef ELLIPTIC_CURVE_DIFFIE_HELLMAN_TESTS
int ecdh_test();
#endif
#ifdef ELLIPTIC_CURVE_DSA_TESTS
int ecdsa_test();
#endif
#ifdef BN_TESTS
int bn_test();
#endif
#ifdef DEFFIE_HELLMAN_TESTS
int dh_test();
#endif
#ifdef SECURE_HASH_ALGORITHM_256
int sha256_test();
#endif
#ifdef SECURE_HASH_ALGORITHM_1
int sha1_test();
#endif
#ifdef THREAD_TESTS
int threads_test();
#endif
#ifdef DNA_PATTERN_MATCHING
int wrapper_seeq_test(globalConfig_t *globalConfig);
int seeq_test();
#endif
#ifdef CUSTOM_TEST
void preCustomTest(globalConfig_t *globalConfig);
int custom_test();
void postCustomTest();
#endif

#ifdef CUSTOM_SHA256_TEST
void initCustomSHA256(globalConfig_t *globalConfig);
int custom_SHA256_test();
void post_SHA256_test();
#endif

#if defined(__cplusplus)
}
#endif


#endif //SGX_APPSBENCH_BENCHTHREAD_H
