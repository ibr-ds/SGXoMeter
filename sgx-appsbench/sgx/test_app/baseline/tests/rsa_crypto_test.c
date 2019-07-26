#ifdef RSA_CRYPTO_TEST


#include "UtilsStructs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifdef PRINT_CHECKS
#define fprintf(stream, msg...) printf(msg)
#define fflush(...)
#else
#define fprintf(stream, msg...)
#define fflush(...)
#endif

static globalConfig_t *globConfPtr;
static char *rsa_message;





void pre_rsa_crypto_test(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    rsa_message = (char *) malloc(globalConfig->RSA_MESSAGE_LEN * sizeof(char));
    if(rsa_message == NULL)
    {
        fprintf(stderr, "Malloc failed!");
    }
    for(int i = 0; i < globalConfig->RSA_MESSAGE_LEN; i++)
    {
        rsa_message[i] = 'a';
    }
}


void post_rsa_crypto_test()
{
    free(rsa_message);
}


int rsa_crypto_test()
{
    printf("RSA CRYPTO IS READY and has the string %s\n", rsa_message);
    return 0;
}

#endif

