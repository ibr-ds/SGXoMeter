#ifdef RSA_CRYPTO_TEST

#include "UtilsStructs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#ifdef SGX_SDK_CONTEXT
    #include <sgx.h>  
    #ifndef TEST_CHECK
        #define TEST_CHECK(status)	\
        {    \
            if (status != SGX_SUCCESS) {    \
                printf("OCALL status check failed %s(%d), status = %d\n", __FUNCTION__, __LINE__, status);    \
                abort();    \
            }    \
        }
    #endif  
#endif
#ifdef OE_ENCLAVE_CONTEXT
    #include <openenclave/enclave.h> 
    #ifndef TEST_CHECK
        #define TEST_CHECK(status)	\
        {    \
            if (status != OE_OK) {    \
                printf("OCALL status check failed %s(%d), status = %d\n", __FUNCTION__, __LINE__, status);    \
                abort();    \
            }    \
        }
    #endif
#endif
#ifndef BASELINE_CONTEXT
    #ifdef PRINT_CHECKS
        #define fprintf(stream, msg...) printf(msg)
        #define fflush(...)
    #else
        #define fprintf(stream, msg...)
        #define fflush(...)
    #endif
#else
    #ifndef PRINT_CHECKS
    #define fprintf(stream, msg...)
    #define fflush(...)
    #endif
#endif

static globalConfig_t *globConfPtr;
static unsigned char *rsa_message;
RSA *keypair;
static char *errMsg;


void pre_rsa_crypto_test(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    size_t rsa_message_size = globConfPtr->RSA_MESSAGE_LEN * sizeof(unsigned char);
    rsa_message = (unsigned char *) malloc(rsa_message_size + 1);

    if(rsa_message == NULL)
    {
        errMsg = "Malloc failed!\n";
        goto err;
    }
    for(int i = 0; i < globalConfig->RSA_MESSAGE_LEN; i++)
    {
        rsa_message[i] = 'a';
    }
    rsa_message[rsa_message_size] = '\0';

    BIGNUM *bn = BN_new();
    if (bn == NULL)
    {
        errMsg = "BN_new failure!\n";
        goto err;
    }
    int ret = BN_set_word(bn, RSA_F4);
    if (!ret)
    {
        errMsg = "BN_set_word failure!\n";
        goto err;
    }

    keypair = RSA_new();
    if (keypair == NULL)
    {
        errMsg = "RSA_new failure!\n";
        goto err;
    }
    ret = RSA_generate_key_ex(keypair, globConfPtr->RSA_BITS, bn, NULL);
    if (!ret)
    {
        errMsg = "RSA_generate_key_ex failure!\n";
        goto err;
    }


 err:
    if (!ret || keypair == NULL)
    {
        #ifdef SGX_SDK_CONTEXT
        sgx_status_t sgx_ret = uprint(errMsg);
        TEST_CHECK(sgx_ret);
        #endif
        #ifdef OE_ENCLAVE_CONTEXT
        oe_result_t sgx_ret = printf(errMsg);
        TEST_CHECK(sgx_ret);
        #endif
        #ifdef BASELINE_CONTEXT
            fprintf(stderr, errMsg);
        #endif
        if(bn != NULL)
        {
            BN_free(bn);
        }
        if(keypair != NULL)
        {
            RSA_free(keypair);
        }
        if(rsa_message != NULL)
        {
            free(rsa_message);
        }
        #ifndef BASELINE_CONTEXT
            sgx_ret = usgx_exit(1);
            TEST_CHECK(sgx_ret);
            return;
        #else
            exit(1);
        #endif
    }

    BN_free(bn);
}


void post_rsa_crypto_test()
{
    free(rsa_message);
    RSA_free(keypair);
}

#define ERROR -1
int rsa_crypto_test()
{
    int rsaMsgLen = globConfPtr->RSA_MESSAGE_LEN;
    unsigned char encodedText[(globConfPtr->RSA_BITS / 8)]; //ToDo message length should not be longer than (rsabits/8 - 11)
    unsigned char decodedText[rsaMsgLen];
    int rsa_len, out_len;

    rsa_len = RSA_public_encrypt(rsaMsgLen, rsa_message, encodedText, keypair, RSA_PKCS1_PADDING);

    if(rsa_len == ERROR)
    {
        errMsg = "encryption failed!";
        goto error;
    }

    out_len = RSA_private_decrypt(rsa_len, encodedText, decodedText, keypair, RSA_PKCS1_PADDING);
    decodedText[out_len] = '\0';
    if(out_len != rsaMsgLen || memcmp(decodedText, rsa_message, rsaMsgLen) != 0)
    {
        errMsg = "decryption failed!";
        goto error;
    }
    return 0;

 error:
    fprintf(stderr, errMsg);
    return 1;

}

#endif

