//
// Created by moe on 27.11.19.
//
#ifdef SGX_ENCRYPTO_TEST

#include <assert.h>
#include <sgx_tcrypto.h>
#include "UtilsStructs.h"
#include "cryptoMemset.h"
#include "sgx_error.h"



#ifdef PRINT_CHECKS
#define fprintf(stream, msg...) printf(msg)
#define fflush(...)
#else
#define fprintf(stream, msg...)
#define fflush(...)
#endif



static globalConfig_t *globConfPtr;
static char *plainText;

static const char encrypKey[SGX_AESGCM_KEY_SIZE] = "THISISASHAREDKEY";
_Static_assert(sizeof(encrypKey) == sizeof(sgx_aes_gcm_128bit_key_t), "KEY SIZE INVALID");
static const uint8_t initVector[SGX_AESGCM_IV_SIZE] = {0};
_Static_assert(sizeof(initVector) == SGX_AESGCM_IV_SIZE, "initialization vector SIZE INVALID");


void pre_sgx_encrypto_test(globalConfig_t *globalConfig)
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

}

void post_sgx_encrypto_test()
{
    free(plainText);
}

int sgx_encrypto_test()
{
    const uint8_t *p_src = plainText;
    uint32_t src_len = globConfPtr->CRYPTO_BUFLEN;
    uint32_t cipherTextSizeWithMac = src_len + SGX_AESGCM_MAC_SIZE; // the size of the encrypted plain text with the mac appeneded at its end
    uint8_t *cipherTextWithMac = (uint8_t *) malloc(cipherTextSizeWithMac); // destination buffer bigger than the encrypted original packet to append the MAC at the end of the KEY

    sgx_status_t status = sgx_rijndael128GCM_encrypt(
            (sgx_aes_gcm_128bit_key_t*)&encrypKey,
            p_src,
            src_len,
            cipherTextWithMac,
            &initVector,
            SGX_AESGCM_IV_SIZE,
            NULL,
            0,
            cipherTextWithMac + src_len // Where to append the generated GCM MAC
    );

    if (status != SGX_SUCCESS)
    {
        return -1;
    }

    free(cipherTextWithMac);

    return 0;
}

#endif