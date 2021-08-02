//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_GENERATETESTFUNCTIONS_H
#define SGX_APPSBENCH_GENERATETESTFUNCTIONS_H


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
        abort();\
        }\
    GEN_TEST_MODULE_FUNCTION_END(NAME)



/*
 * generating wrapper functions for the chosen test modules
 * these will be added later in the function ptr array
 */

#ifdef SGX_ENCRYPTO_TEST
GEN_TEST_MODULE_FUNCTION(sgx_encrypto_test);
#endif

#ifdef SGX_DECRYPTO_TEST
GEN_TEST_MODULE_FUNCTION(sgx_decrypto_test);
#endif

#ifdef SGX_DECRYPTO_EXT_TEST
GEN_TEST_MODULE_FUNCTION(sgx_decrypto_ext_test);
#endif

#ifdef SGX_DECRYPTO_ENCRYPTO
GEN_TEST_MODULE_FUNCTION(sgx_dencrypto_test);
#endif

#ifdef CUSTOM_TEST
GEN_TEST_MODULE_FUNCTION(custom_test)
#endif

#ifdef ARGON2_TEST
GEN_TEST_MODULE_FUNCTION(argon2_test)
#endif

#ifdef CUSTOM_SHA256_TEST
GEN_TEST_MODULE_FUNCTION(custom_SHA256_test)
#endif

#ifdef RSA_CRYPTO_TEST
GEN_TEST_MODULE_FUNCTION(rsa_crypto_test)
#endif

#ifdef RSA_SIGN_TEST
GEN_TEST_MODULE_FUNCTION(rsa_sign_test)
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

#ifdef MARCEL_TEST
GEN_TEST_MODULE_FUNCTION(marcel_test)
#endif

#ifdef AEAD_AES256GCM_TEST
GEN_TEST_MODULE_FUNCTION(aead_aes256gcm_test)
#endif

#ifdef AEAD_AES256GCM_ENCRYPT_TEST
GEN_TEST_MODULE_FUNCTION(aead_aes256gcm_encrypt_test)
#endif




#endif //SGX_APPSBENCH_GENERATETESTFUNCTIONS_H
