//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_TESTFUNCTIONPOINTERARRAY_H
#define SGX_APPSBENCH_TESTFUNCTIONPOINTERARRAY_H

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

#ifdef ARGON2_TEST
                ,TEST_NAME(argon2_test)
#endif

#ifdef RSA_CRYPTO_TEST
                ,TEST_NAME(rsa_crypto_test)
#endif

#ifdef RSA_SIGN_TEST
                ,TEST_NAME(rsa_sign_test)
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

#endif //SGX_APPSBENCH_TESTFUNCTIONPOINTERARRAY_H
