//
// Created by moe on 27.11.19.
//

#ifdef SGX_DECRYPTO_EXT_TEST

#include <sgx_tcrypto.h>

#include "cryptoMemset.h"
#include "UtilsStructs.h"
#include "ocallDefinitions.h"

#ifdef PRINT_CHECKS
#define fprintf(stream, msg...) printf(msg)
#define fflush(...)
#else
#define fprintf(stream, msg...)
#define fflush(...)
#endif

static globalConfig_t *globConfPtr;
static char *plainText;
static char *externalBufferPtr;

static const char encrypKey[SGX_AESGCM_KEY_SIZE] = "THISISASHAREDKEY";
_Static_assert(sizeof(encrypKey) == sizeof(sgx_aes_gcm_128bit_key_t), "KEY SIZE INVALID");
static const uint8_t initVector[SGX_AESGCM_IV_SIZE] = {0};
_Static_assert(sizeof(initVector) == SGX_AESGCM_IV_SIZE, "initialization vector SIZE INVALID");


static void private_encrypt()
{
    const uint8_t *p_src = plainText;
    uint32_t src_len = globConfPtr->CRYPTO_BUFLEN;


    sgx_status_t status = sgx_rijndael128GCM_encrypt(
            (sgx_aes_gcm_128bit_key_t*)&encrypKey,
            p_src,
            src_len,
            externalBufferPtr,
            &initVector,
            SGX_AESGCM_IV_SIZE,
            NULL,
            0,
            externalBufferPtr + src_len // Where to append the generated GCM MAC
    );

    if (status != SGX_SUCCESS)
    {
        fprintf(stderr, "encypting the plain text privately went wrong!\n");
        return;
    }
}



void pre_sgx_decrypto_ext_test(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    size_t plainBufferSize = globConfPtr->CRYPTO_BUFLEN * sizeof(char);
    plainText = (char *) malloc(plainBufferSize + 1);
    if(plainText == NULL)
    {
        fprintf(stderr, "Malloc failed!");
    }
    for(int i = 0; i < globConfPtr->CRYPTO_BUFLEN; i++)
    {
        plainText[i] = 'a';
    }
    plainText[plainBufferSize] = '\0';
    externalBufferPtr = ocallMalloc(plainBufferSize + SGX_AESGCM_MAC_SIZE);
    if (externalBufferPtr == NULL)
    {
        fprintf(stderr, "failed to allocate the cipher text buffer on the untrusted side!\n");
        return;
    }
    private_encrypt();
}

void post_sgx_decrypto_ext_test()
{
    free(plainText);
    free(externalBufferPtr);
}

int sgx_decrypto_ext_test()
{

    uint32_t src_len = globConfPtr->CRYPTO_BUFLEN;
    uint8_t *p_dst = (uint8_t *) malloc(src_len);

    sgx_status_t status = sgx_rijndael128GCM_decrypt(
            (sgx_aes_gcm_128bit_key_t*)&encrypKey,
            externalBufferPtr,
            src_len,
            p_dst,
            &initVector,
            SGX_AESGCM_IV_SIZE,
            NULL,
            0,
            externalBufferPtr + src_len
    );

    if (status != SGX_SUCCESS)
    {
        return NULL;
    }

    if (memcmp(p_dst, plainText, src_len) != 0)
    {
        return 1;
    }

    free(p_dst);

    return 0;
}

#endif
