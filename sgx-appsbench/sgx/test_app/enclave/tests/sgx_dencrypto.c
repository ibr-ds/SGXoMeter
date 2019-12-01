//
// Created by moe on 01.12.19.
//

#ifdef SGX_DECRYPTO_ENCRYPTO

#include <assert.h>
#include <sgx_tcrypto.h>
#include "UtilsStructs.h"
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
static char *cipherText;

static const char encrypKey[SGX_AESGCM_KEY_SIZE] = "THISISASHAREDKEY";
_Static_assert(sizeof(encrypKey) == sizeof(sgx_aes_gcm_128bit_key_t), "KEY SIZE INVALID");
static const uint8_t initVector[SGX_AESGCM_IV_SIZE] = {0};
_Static_assert(sizeof(initVector) == SGX_AESGCM_IV_SIZE, "initialization vector SIZE INVALID");



static void private_encrypt(char *plText, char *ciphText)
{
    const uint8_t *p_src = plText;
    uint32_t src_len = globConfPtr->CRYPTO_BUFLEN;
    uint32_t cipherTextSizeWithMac = src_len + SGX_AESGCM_MAC_SIZE; // the size of the encrypted plain text with the mac appeneded at its end
    ciphText = (uint8_t *) malloc(cipherTextSizeWithMac); // destination buffer bigger than the encrypted original packet to append the MAC at the end of the KEY

    sgx_status_t status = sgx_rijndael128GCM_encrypt(
            (sgx_aes_gcm_128bit_key_t*)&encrypKey,
            p_src,
            src_len,
            ciphText,
            &initVector,
            SGX_AESGCM_IV_SIZE,
            NULL,
            0,
            ciphText + src_len // Where to append the generated GCM MAC
    );

    if (status != SGX_SUCCESS)
    {
        fprintf(stderr, "encypting the plain text privately went wrong!\n");
        return;
    }
}

void pre_sgx_dencrypto_test(globalConfig_t *globalConfig)
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
    private_encrypt(plainText, cipherText);
}

void post_sgx_dencrypto_test()
{
    free(plainText);
    free(cipherText);
}

int sgx_dencrypto_test()
{
	uint32_t src_len = globConfPtr->CRYPTO_BUFLEN;
	uint8_t *p_dst = (uint8_t *) malloc(src_len);

	sgx_status_t status = sgx_rijndael128GCM_decrypt(
		(sgx_aes_gcm_128bit_key_t*)&encrypKey,
		cipherText,
		src_len,
		p_dst,
		&initVector,
		SGX_AESGCM_IV_SIZE,
		NULL,
		0,
		cipherText + src_len
	);

	if (status != SGX_SUCCESS)
	{
		return NULL;
	}

	if (memcmp(p_dst, plainText, src_len) != 0)
	{
        return 1;
	}

	uint8_t *enc_dst = NULL;
    private_encrypt(p_dst, enc_dst);

	if (memcmp(enc_dst, cipherText, src_len + SGX_AESGCM_MAC_SIZE) != 0)
	{
        return 1;
	}
    free(p_dst);
    free(enc_dst);

	return 0;
}

#endif
