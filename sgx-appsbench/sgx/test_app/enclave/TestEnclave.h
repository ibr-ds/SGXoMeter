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

#ifndef _TESTENCLAVE_H_
#define _TESTENCLAVE_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "UtilsStructs.h"

#define TEST_CHECK(status)	\
{	\
	if (status != SGX_SUCCESS) {	\
		printf("OCALL status check failed %s(%d), status = %d\n", __FUNCTION__, __LINE__, status);	\
		abort();	\
	}	\
}

#if defined(__cplusplus)
extern "C" {
#endif

void printf(const char *fmt, ...);

int puts(const char* str);
int fflush(void* stream);
void exit(int status);

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
#ifdef RSA_CRYPTO_TEST
void pre_rsa_crypto_test(globalConfig_t *globalConfig);
int rsa_crypto_test();
void post_rsa_crypto_test();
#endif
#ifdef RSA_SIGN_TEST
void pre_rsa_sign_test(globalConfig_t *globalConfig);
int rsa_sign_test();
void post_rsa_sign_test();
#endif

#if defined(__cplusplus)
}
#endif

#endif /* !_TESTENCLAVE_H_ */
