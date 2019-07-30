//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_PRETESTFUNCTIONCALLS_H
#define SGX_APPSBENCH_PRETESTFUNCTIONCALLS_H

#ifdef CUSTOM_SHA256_TEST
initCustomSHA256(GLOBAL_CONFIG);
#endif

#ifdef CUSTOM_TEST
preCustomTest(GLOBAL_CONFIG);
#endif

#ifdef RSA_CRYPTO_TEST
pre_rsa_crypto_test(GLOBAL_CONFIG);
#endif

#ifdef RSA_SIGN_TEST
pre_rsa_sign_test(GLOBAL_CONFIG);
#endif

#ifdef ARGON2_TEST
pre_argon2_test(GLOBAL_CONFIG);
#endif

#ifdef DNA_PATTERN_MATCHING
pre_seeq_test(GLOBAL_CONFIG);
#endif

#endif //SGX_APPSBENCH_PRETESTFUNCTIONCALLS_H
