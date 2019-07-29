//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_TESTFUNCTIONSSIGNATURES_H
#define SGX_APPSBENCH_TESTFUNCTIONSSIGNATURES_H

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
int  rsa_crypto_test();
void post_rsa_crypto_test();
#endif
#ifdef RSA_SIGN_TEST
void pre_rsa_sign_test(globalConfig_t *globalConfig);
int  rsa_sign_test();
void post_rsa_sign_test();
#endif

#ifdef ARGON2_TEST
void pre_argon2_test(globalConfig_t *globalConfig);
int  argon2_test();
void post_argon2_test();
#endif

#endif //SGX_APPSBENCH_TESTFUNCTIONSSIGNATURES_H
