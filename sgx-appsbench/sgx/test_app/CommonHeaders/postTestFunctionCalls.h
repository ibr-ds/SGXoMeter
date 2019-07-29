//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_POSTTESTFUNCTIONCALLS_H
#define SGX_APPSBENCH_POSTTESTFUNCTIONCALLS_H

#ifdef CUSTOM_SHA256_TEST
if(strcmp(test_names[test_id], "custom SHA256 test") == 0)
    {
        post_SHA256_test();
    }
#endif

#ifdef CUSTOM_TEST
if(strcmp(test_names[test_id], "custom test") == 0)
    {
        postCustomTest();
    }
#endif

#ifdef RSA_CRYPTO_TEST
if(strcmp(test_names[test_id], "rsa crypto test") == 0)
    {
        post_rsa_crypto_test();
    }
#endif

#ifdef RSA_SIGN_TEST
if(strcmp(test_names[test_id], "rsa signing test") == 0)
    {
        post_rsa_sign_test();
    }
#endif

#ifdef ARGON2_TEST
if(strcmp(test_names[test_id], "argon2 test") == 0)
    {
        post_argon2_test();
    }
#endif

#endif //SGX_APPSBENCH_POSTTESTFUNCTIONCALLS_H
