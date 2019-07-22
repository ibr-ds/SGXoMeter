//
// Created by moe on 16.07.19.
//
#define CUSTOM_SHA256_TEST
#ifdef CUSTOM_SHA256_TEST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include <openssl/sha.h>
#include <openssl/evp.h>
#include <UtilsStructs.h>

#define stdout ((void*)1)
#define stderr ((void*)2)

#ifdef PRINT_CHECKS
#define fprintf(stream, msg...) printf(msg)
#define fflush(...)
#else
#define fprintf(stream, msg...)
#define fflush(...)
#endif


char *toHashStr;
static globalConfig_t *globConfPtr;
void initCustomSHA256(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    toHashStr = (char *) malloc(globalConfig->HASH256_LEN * sizeof(char));
    for(int i = 0; i < globalConfig->HASH256_LEN; i++)
    {
        toHashStr[i] = 'a';
    }
}


int custom_SHA256_test()
{
    unsigned char md[SHA256_DIGEST_LENGTH];
    fprintf(stdout, "Testing SHA-256 ");
    if(EVP_Digest(toHashStr, globConfPtr->HASH256_LEN , md, NULL, EVP_sha256(), NULL) != 1)
    {
        fflush(stdout);
        fprintf(stderr, "\nTEST SHA256 FAILED.\n");
        return 1;
    } else {
        fprintf(stdout, ".");
        fflush(stdout);
    return 0;
    }
}

#endif
