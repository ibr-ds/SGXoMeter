//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_POSTTESTFUNCTIONCALLS_H
#define SGX_APPSBENCH_POSTTESTFUNCTIONCALLS_H


for (int test_id = 1; test_id < NUM_OF_TEST_MODULES+DUMMY_INDEX; ++test_id)
{
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

#ifdef SGX_ENCRYPTO_TEST
if(strcmp(test_names[test_id], "sgx encrypto test") == 0)
    {
        post_sgx_encrypto_test();
    }
#endif

#ifdef SGX_DECRYPTO_TEST
if(strcmp(test_names[test_id], "sgx decrypto test") == 0)
    {
        post_sgx_decrypto_test();
    }
#endif

#ifdef SGX_DECRYPTO_EXT_TEST
if(strcmp(test_names[test_id], "sgx decrypto ext test") == 0)
    {
        post_sgx_decrypto_ext_test();
    }
#endif

#ifdef SGX_DECRYPTO_ENCRYPTO
if(strcmp(test_names[test_id], "sgx decrypto encrypto test") == 0)
    {
        post_sgx_dencrypto_test();
    }
#endif

#ifdef AEAD_AES256GCM_ENCRYPT_TEST
if(strcmp(test_names[test_id], "AEAD AES256GCM ENCRYPT TEST") == 0)
    {
        post_aead_aes256gcm_encrypt_test();
    }
#endif

#ifdef AEAD_AES256GCM_DECRYPT_TEST
if(strcmp(test_names[test_id], "AEAD AES256GCM DECRYPT TEST") == 0)
    {
        post_aead_aes256gcm_decrypt_test();
    }
#endif

#ifdef EXCEED_EPC_TEST
if(strcmp(test_names[test_id], "EXCEED EPC TEST") == 0)
    {
        post_exceed_epc_test();
    }
#endif

}
#endif //SGX_APPSBENCH_POSTTESTFUNCTIONCALLS_H
