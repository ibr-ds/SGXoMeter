#include "sodium.h"

#include <stdarg.h>
#include <stdio.h>      /* vsnprintf */
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <assert.h>
#include "UtilsStructs.h"

static globalConfig_t *globConfPtr;

unsigned char nonce[crypto_aead_aes256gcm_NPUBBYTES];
unsigned char key[crypto_aead_aes256gcm_KEYBYTES];
unsigned char      *ciphertext;
unsigned long long ciphertext_len;
static char *plainText;


void pre_aead_aes256gcm_encrypt_test(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    if (sodium_init() == -1) {
        return 1;
    }
    if (crypto_aead_aes256gcm_is_available() == 0) {
        return 1; /* Not available on this CPU */
    }
    crypto_aead_aes256gcm_keygen(key);
    randombytes_buf(nonce, sizeof nonce);

    
    size_t plainBufferSize = globConfPtr->CRYPTO_BUFLEN * sizeof(char);
    plainText = (char *) malloc(plainBufferSize + 1);
    if(plainText == NULL)
    {
        //fprintf(stderr, "Malloc failed!");
    }
    for(int i = 0; i < globConfPtr->CRYPTO_BUFLEN; i++)
    {
        plainText[i] = 'a';
    }
    plainText[plainBufferSize] = '\0';
    /*
    key = (unsigned char *) sodium_malloc(crypto_aead_aes256gcm_KEYBYTES);
    nonce = (unsigned char *) sodium_malloc(crypto_aead_aes256gcm_NPUBBYTES);
    mac = (unsigned char *) sodium_malloc(crypto_aead_aes256gcm_ABYTES);
    */
}

void post_aead_aes256gcm_encrypt_test()
{
    free(plainText);
}

int aead_aes256gcm_encrypt_test()
{
    uint32_t plaintext_len = globConfPtr->CRYPTO_BUFLEN;
    uint32_t ciphertextSize =  plaintext_len + crypto_aead_aes256gcm_ABYTES;
    ciphertext = (char *) malloc(ciphertextSize);
    

    crypto_aead_aes256gcm_encrypt(ciphertext, &ciphertext_len,
                                      plainText, plaintext_len,
                                      NULL, 0, NULL, nonce, key);

    free(ciphertext);
    return 0;

}
