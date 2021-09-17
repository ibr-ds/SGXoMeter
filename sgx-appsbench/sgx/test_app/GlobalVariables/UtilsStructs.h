#ifndef _UTILS_STRUCTS_
#define _UTILS_STRUCTS_

#include "GlobalMacros.h" //ToDo delete this later as this will be obselete through the CMAKELISTS.txt.  Macros will be set in the CMAKE
#include "TestMacros.h" //ToDo delete this later as this will be obselete through the CMAKELISTS.txt.  Macros will be set in the CMAKE
#include <stdint.h>
#include <stdio.h>


typedef struct globalConfig{
#ifdef WRITE_LOG_FILE
    char *DATA_FILE_NAME;
#endif

    int NUM_OF_ITERATION;
    uint64_t RUNTIME;
    uint64_t WARMUP_TIME;
    uint64_t NUM_OF_WTHREADS;

#ifdef CUSTOM_SHA256_TEST
    size_t HASH256_LEN;
#endif

#if defined(SGX_ENCRYPTO_TEST) || defined(SGX_DECRYPTO_TEST) || defined(SGX_DECRYPTO_EXT_TEST) || defined(SGX_DECRYPTO_ENCRYPTO) || defined(AEAD_AES256GCM_ENCRYPT_TEST) || defined(AEAD_AES256GCM_DECRYPT_TEST)
    size_t CRYPTO_BUFLEN;
#endif

#if  defined(RSA_KEY_GEN) || defined(RSA_CRYPTO_TEST) || defined(RSA_SIGN_TEST)
    int RSA_BITS;
#endif

#if defined(RSA_CRYPTO_TEST) || defined(RSA_SIGN_TEST)
    size_t RSA_MESSAGE_LEN;
#endif

#ifdef DNA_PATTERN_MATCHING
    char *DNA_INPUT;
    char *PATTERN_INPUT;
    int SHOW_DIST;
    int SHOW_POS;
    int SHOW_LINE;
    int PRINT_LINE;
    int MATCH_ONLY;
    int COUNT;
    int COMPACT;
    int DIST;
    int VERBOSE;
    int END_LINE;
    int PREFIX;
    int INVERT;
    int BEST;
    int NON_DNA;
    int ALL;
    size_t MEMORY;
#endif

#ifdef EXCEED_EPC_TEST_RAND
    size_t READ_BUFLEN;
#endif

} globalConfig_t;




#endif
