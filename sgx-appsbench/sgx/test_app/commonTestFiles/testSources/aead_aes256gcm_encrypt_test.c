#ifdef AEAD_AES256GCM_ENCRYPT_TEST
#include "sodium.h"

#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */
#include <string.h>
#include <stdlib.h>
#include "UtilsStructs.h"

static globalConfig_t *globConfPtr;

unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES];
unsigned char key[crypto_aead_aes256gcm_KEYBYTES];
unsigned char      *ciphertextEncrypt;
unsigned long long ciphertext_len;
static char *plainTextEncrypt;

/*
    Prepare the random buffer for module execution
*/
void pre_aead_aes256gcm_encrypt_test(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    if (sodium_init() == -1) {
        return 1;
    }
    // if (crypto_aead_aes256gcm_is_available() == 0) {
    //     //return 1; /* Not available on this CPU */     --> Diese Anweisung funktioniert nicht in SGX 
    // }
    crypto_aead_aes256gcm_keygen(key);
    randombytes_buf(nonce, sizeof nonce);

    
    size_t plainBufferSize = globConfPtr->CRYPTO_BUFLEN * sizeof(char);
    plainTextEncrypt = (char *) malloc(plainBufferSize + 1);
    if(plainTextEncrypt == NULL)
    {
        return 1; // Malloc failed
    }
    for(int i = 0; i < globConfPtr->CRYPTO_BUFLEN; i++)
    {
        plainTextEncrypt[i] = 'a';
    }
    plainTextEncrypt[plainBufferSize] = '\0';

    size_t ciphertextSize =  plainBufferSize + crypto_aead_aes256gcm_ABYTES;
    ciphertextEncrypt = (char *) malloc(ciphertextSize);

}

/*Executed after encrypt test */
void post_aead_aes256gcm_encrypt_test()
{
    free(plainTextEncrypt);
    free(ciphertextEncrypt);
}

/*Actual aead_aes256gcm_encrypt_test */
int aead_aes256gcm_encrypt_test()
{
    uint32_t plaintext_len = globConfPtr->CRYPTO_BUFLEN;
    crypto_aead_aes256gcm_encrypt(ciphertextEncrypt, &ciphertext_len,
                                      plainTextEncrypt, plaintext_len,
                                     NULL, 0, NULL, nonce, key);

    return 0;

}
#endif