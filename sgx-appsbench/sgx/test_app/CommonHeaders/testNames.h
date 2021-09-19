//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_TESTNAMES_H
#define SGX_APPSBENCH_TESTNAMES_H


#define DUMMY_INDEX 1
#define MAX_TEST_NAME_LENGTH 32

static char test_names[NUM_OF_TEST_MODULES + DUMMY_INDEX][MAX_TEST_NAME_LENGTH] = {
        "NONE"

#ifdef SGX_ENCRYPTO_TEST
        , "sgx encrypto test"
#endif

#ifdef SGX_DECRYPTO_TEST
        , "sgx decrypto test"
#endif

#ifdef SGX_DECRYPTO_EXT_TEST
        , "sgx decrypto ext test"
#endif

#ifdef SGX_DECRYPTO_ENCRYPTO
        , "sgx decrypto encrypto test"
#endif

#ifdef CUSTOM_SHA256_TEST
        , "custom SHA256 test"
#endif

#ifdef CUSTOM_TEST
        , "custom test"
#endif

#ifdef ARGON2_TEST
        , "argon2 test"
#endif

#ifdef RSA_CRYPTO_TEST
        , "rsa crypto test"
#endif

#ifdef RSA_SIGN_TEST
        , "rsa signing test"
#endif

#ifdef RSA_KEY_GEN
        , "rsa key gen"
#endif

#ifdef ELLIPTIC_CURVE_KEY_GEN
        , "EC key gen"
#endif

#ifdef DNA_PATTERN_MATCHING
        , "DNA matching"
#endif

#ifdef RSA_TESTS
        , "RSA tests"
#endif

#ifdef ELLIPTIC_CURVE_TESTS
        , "EC tests"
#endif

#ifdef ELLIPTIC_CURVE_DIFFIE_HELLMAN_TESTS
        , "EC & DH tests"
#endif

#ifdef ELLIPTIC_CURVE_DSA_TESTS
        , "EC & DSA tests"
#endif

#ifdef BN_TESTS
        , "BN Tests"
#endif

#ifdef DEFFIE_HELLMAN_TESTS
        , "DH tests"
#endif

#ifdef SECURE_HASH_ALGORITHM_256
        , "SHA256"
#endif

#ifdef SECURE_HASH_ALGORITHM_1
        , "SHA1"
#endif

#ifdef THREAD_TESTS
        , "Multi-Thread tests"
#endif

#ifdef MARCEL_TEST
        , "Marcel Test"
#endif

#ifdef AEAD_AES256GCM_TEST
        , "AEAD AES256GCM TEST"
#endif

#ifdef AEAD_AES256GCM_ENCRYPT_TEST
        , "AEAD AES256GCM ENCRYPT TEST"
#endif

#ifdef AEAD_AES256GCM_DECRYPT_TEST
        , "AEAD AES256GCM DECRYPT TEST"
#endif

#ifdef EXCEED_EPC_TEST_RAND
        , "EXCEED EPC TEST RAND"
#endif

#ifdef EXCEED_EPC_TEST_SEQ
        , "EXCEED EPC TEST SEQ"
#endif

};



#endif //SGX_APPSBENCH_TESTNAMES_H
