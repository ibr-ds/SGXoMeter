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


#include <stdio.h>      /* vsnprintf */
#include <stdarg.h>

#include "TestEnclave.h"
#include "TestEnclave_t.h"  /* print_string */
#include "tSgxSSL_api.h"

#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <sgx_tae_service.h>


#define ADD_ENTROPY_SIZE	32


/* 
 * printf: 
 *   Invokes OCALL to display the enclave buffer to the terminal.
 */
void printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    uprint(buf);
}

typedef void CRYPTO_RWLOCK;

struct evp_pkey_st {
    int type;
    int save_type;
    int references;
    const EVP_PKEY_ASN1_METHOD *ameth;
    ENGINE *engine;
    union {
        char *ptr;
# ifndef OPENSSL_NO_RSA
        struct rsa_st *rsa;     /* RSA */
# endif
# ifndef OPENSSL_NO_DSA
        struct dsa_st *dsa;     /* DSA */
# endif
# ifndef OPENSSL_NO_DH
        struct dh_st *dh;       /* DH */
# endif
# ifndef OPENSSL_NO_EC
        struct ec_key_st *ec;   /* ECC */
# endif
    } pkey;
    int save_parameters;
    STACK_OF(X509_ATTRIBUTE) *attributes; /* [ 0 ] */
    CRYPTO_RWLOCK *lock;
} /* EVP_PKEY */ ;


#ifdef RSA_KEY_GEN
int rsa_key_gen()
{
	BIGNUM *bn = BN_new();
	if (bn == NULL) {
		printf("BN_new failure: %ld\n", ERR_get_error());
	    return 1;
	}
	int ret = BN_set_word(bn, RSA_F4);
    if (!ret) {
       	printf("BN_set_word failure\n");
	    return 1;
	}
	
	RSA *keypair = RSA_new();
	if (keypair == NULL) {
		printf("RSA_new failure: %ld\n", ERR_get_error());
	    return 1;
	}
	ret = RSA_generate_key_ex(keypair, 4096, bn, NULL);
	if (!ret) {
        printf("RSA_generate_key_ex failure: %ld\n", ERR_get_error());
	    return 1;
	}

	EVP_PKEY *evp_pkey = EVP_PKEY_new();
	if (evp_pkey == NULL) {
		printf("EVP_PKEY_new failure: %ld\n", ERR_get_error());
		return 1;
	}
	EVP_PKEY_assign_RSA(evp_pkey, keypair);

	// public key - string
	int len = i2d_PublicKey(evp_pkey, NULL);
	unsigned char *buf = (unsigned char *) malloc (len + 1);
	unsigned char *tbuf = buf;
	i2d_PublicKey(evp_pkey, &tbuf);

#ifdef PRINT_CHECKS
	// print public key
	printf ("{\"public\":\"");
	int i;
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	// private key - string
	len = i2d_PrivateKey(evp_pkey, NULL);
	buf = (unsigned char *) malloc (len + 1);
	tbuf = buf;
	i2d_PrivateKey(evp_pkey, &tbuf);


#ifdef PRINT_CHECKS
    // print private key
	printf ("{\"private\":\"");
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	BN_free(bn);

	EVP_PKEY_free(evp_pkey);

	if (evp_pkey->pkey.ptr != NULL) {
	  RSA_free(keypair);
	}
	return 0;
}

#endif //RSA KEY GEN

#ifdef ELLIPTIC_CURVE_KEY_GEN
int ec_key_gen()
{
	unsigned char entropy_buf[ADD_ENTROPY_SIZE] = {0};

	RAND_add(entropy_buf, sizeof(entropy_buf), ADD_ENTROPY_SIZE);
	RAND_seed(entropy_buf, sizeof(entropy_buf));

	EC_KEY * ec = NULL;
    int eccgroup;
    eccgroup = OBJ_txt2nid("secp384r1");
    ec = EC_KEY_new_by_curve_name(eccgroup);
    if (ec == NULL) {
    	printf("EC_KEY_new_by_curve_name failure: %ld\n", ERR_get_error());
	    return 1;
    }
    
	EC_KEY_set_asn1_flag(ec, OPENSSL_EC_NAMED_CURVE);

	int ret = EC_KEY_generate_key(ec);
	if (!ret) {
        printf("EC_KEY_generate_key failure\n");
	    return 1;
	}

	EVP_PKEY *ec_pkey = EVP_PKEY_new();
	if (ec_pkey == NULL) {
		printf("EVP_PKEY_new failure: %ld\n", ERR_get_error());
		return 1;
	}
	EVP_PKEY_assign_EC_KEY(ec_pkey, ec);

	// public key - string
	int len = i2d_PublicKey(ec_pkey, NULL);
	unsigned char *buf = (unsigned char *) malloc (len + 1);
	unsigned char *tbuf = buf;
	i2d_PublicKey(ec_pkey, &tbuf);


#ifdef PRINT_CHECKS
    // print public key
	printf ("{\"public\":\"");
	int i;
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	// private key - string
	len = i2d_PrivateKey(ec_pkey, NULL);
	buf = (unsigned char *) malloc (len + 1);
	tbuf = buf;
	i2d_PrivateKey(ec_pkey, &tbuf);

#ifdef PRINT_CHECKS
	// print private key
	printf ("{\"private\":\"");
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	EVP_PKEY_free(ec_pkey);
	if (ec_pkey->pkey.ptr != NULL) {
	  EC_KEY_free(ec);
	}
	return 0;
}

#endif  //ELLIPTIC CURVE KEY GEN

int vprintf_cb(Stream_t stream, const char * fmt, va_list arg)
{
	char buf[BUFSIZ] = {'\0'};

	int res = vsnprintf(buf, BUFSIZ, fmt, arg);
	if (res >=0) {
		sgx_status_t sgx_ret = uprint((const char *) buf);
		TEST_CHECK(sgx_ret);
	}
	return res;
}


/*
 * Local variables referring global variables, which their values are changed from multiple threads
 */
static volatile int do_bench = 0;
volatile uint64_t *bench_counter = 0;
static globalConfig_t *GLOBAL_CONFIG;




/*
 * This is a wrapper inorder to be able to added this function to the function pointer array later
 */
#ifdef DNA_PATTERN_MATCHING
int seeq_test()
{
    return wrapper_seeq_test(GLOBAL_CONFIG);
}
#endif


#ifdef PRINT_CHECKS
#define GEN_TEST_MODULE_FUNCTION_END(NAME)  printf("Test %s completed\n", #NAME);\
}
#else
#define GEN_TEST_MODULE_FUNCTION_END(NAME)  }
#endif

#define TEST_NAME(NAME) execute_##NAME

#define GEN_TEST_MODULE_FUNCTION(NAME) static void execute_##NAME() \
    { \
        int ret = 0; \
        ret = NAME(); \
        if(ret != 0) \
        { \
        printf("%s has failed!\n", #NAME); \
        }\
    GEN_TEST_MODULE_FUNCTION_END(NAME)



#define TEST_NAME(NAME) execute_##NAME

/*
 * generating wrapper functions for the chosen test modules
 * these will be added later in the function ptr array
 */
#ifdef CUSTOM_TEST
GEN_TEST_MODULE_FUNCTION(custom_test)
#endif

#ifdef CUSTOM_SHA256_TEST
GEN_TEST_MODULE_FUNCTION(custom_SHA256_test)
#endif

#ifdef RSA_KEY_GEN
GEN_TEST_MODULE_FUNCTION(rsa_key_gen)
#endif

#ifdef ELLIPTIC_CURVE_KEY_GEN
GEN_TEST_MODULE_FUNCTION(ec_key_gen)
#endif

#ifdef DNA_PATTERN_MATCHING
GEN_TEST_MODULE_FUNCTION(seeq_test)
#endif

#ifdef RSA_TESTS
GEN_TEST_MODULE_FUNCTION(rsa_test)
#endif

#ifdef ELLIPTIC_CURVE_TESTS
GEN_TEST_MODULE_FUNCTION(ec_test)
#endif

#ifdef ELLIPTIC_CURVE_DIFFIE_HELLMAN_TESTS
GEN_TEST_MODULE_FUNCTION(ecdh_test)
#endif

#ifdef ELLIPTIC_CURVE_DSA_TESTS
GEN_TEST_MODULE_FUNCTION(ecdsa_test)
#endif

#ifdef BN_TESTS
GEN_TEST_MODULE_FUNCTION(bn_test)
#endif

#ifdef DEFFIE_HELLMAN_TESTS
GEN_TEST_MODULE_FUNCTION(dh_test)
#endif

#ifdef SECURE_HASH_ALGORITHM_256
GEN_TEST_MODULE_FUNCTION(sha256_test)
#endif

#ifdef SECURE_HASH_ALGORITHM_1
GEN_TEST_MODULE_FUNCTION(sha1_test)
#endif

#ifdef THREAD_TESTS
GEN_TEST_MODULE_FUNCTION(threads_test)
#endif



#define DUMMY_INDEX 1
/*
 * This is only a dummy to solve the problem of adding the test modules hybridly (P.S it won*t be called)
 * in case for some reason it gets called you will be notified with the message written in it
 */
void dummy()
{
    printf("dummy is called! something is wrong\n!");
}

/*
 * The function pointer array of the generated chosen test modules
 * it also contains at first a dummy empty function to avoid the adding ',' comma problem
 */
void (*testFuncPtr[NUM_OF_TEST_MODULES + DUMMY_INDEX])() =
    {
                 dummy
#ifdef CUSTOM_SHA256_TEST
                ,TEST_NAME(custom_SHA256_test)
#endif

#ifdef CUSTOM_TEST
                ,TEST_NAME(custom_test)
#endif

#ifdef RSA_KEY_GEN
                ,TEST_NAME(rsa_key_gen)
#endif

#ifdef ELLIPTIC_CURVE_KEY_GEN
                ,TEST_NAME(ec_key_gen)
#endif

#ifdef DNA_PATTERN_MATCHING
                ,TEST_NAME(seeq_test)
#endif

#ifdef RSA_TESTS
                ,TEST_NAME(rsa_test)
#endif

#ifdef ELLIPTIC_CURVE_TESTS
                ,TEST_NAME(ec_test)
#endif

#ifdef ELLIPTIC_CURVE_DIFFIE_HELLMAN_TESTS
                ,TEST_NAME(ecdh_test)
#endif

#ifdef ELLIPTIC_CURVE_DSA_TESTS
                ,TEST_NAME(ecdsa_test)
#endif

#ifdef BN_TESTS
                ,TEST_NAME(bn_test)
#endif

#ifdef DEFFIE_HELLMAN_TESTS
                ,TEST_NAME(dh_test)
#endif

#ifdef SECURE_HASH_ALGORITHM_256
                ,TEST_NAME(sha256_test)
#endif

#ifdef SECURE_HASH_ALGORITHM_1
                ,TEST_NAME(sha1_test)
#endif

#ifdef THREAD_TESTS
                ,TEST_NAME(threads_test)
#endif
    };


extern "C" void ecall_set_config(uint64_t *ctr, void *globalConfig)
{
    bench_counter = ctr;
    if(globalConfig != NULL)
    {
        GLOBAL_CONFIG = (globalConfig_t *)globalConfig;
    }
    SGXSSLSetPrintToStdoutStderrCB(vprintf_cb);
    OPENSSL_init_crypto(0, NULL);
#ifdef CUSTOM_SHA256_TEST
    initCustomSHA256(GLOBAL_CONFIG);   //ToDo this might not work. If so build a wrapper like seeqtest
#endif
}

/*
 * The 3 Benchmark status
 */
#define PAUSED    0
#define RUNNING   1
#define STOPED    2

extern "C" void ecall_start_bench()
{
    do_bench = RUNNING;
}

extern "C" void ecall_stop_bench(void)
{
    do_bench = STOPED;
}

extern "C" void ecall_run_bench(int test_id)
{

    while(do_bench == PAUSED)
    { __asm__("pause");}

    int iterCounter = 0;

#ifdef PRINT_CHECKS
    printf("Start tests\n");
#endif

    while(do_bench == RUNNING)
    {
        //execute_test();
        (*testFuncPtr[test_id])();
        __sync_fetch_and_add(bench_counter, 1);

        if(GLOBAL_CONFIG->NUM_OF_ITERATION > 0) {
            iterCounter++;
            //check the counter either against the given one with a query or the one set globally
            if(iterCounter == GLOBAL_CONFIG->NUM_OF_ITERATION)      break;
        }
    }
    //Reset the benchmark in case of multiple test modules to run after each other
    do_bench = PAUSED;
}
