#ifndef _GLOBAL_VARIABLES_
#define _GLOBAL_VARIABLES_

#include "UtilsStructs.h"

#ifdef RUNTIME_PARSER

    extern globalConfig_t GLOBAL_CONFIG;


#else

    globalConfig_t GLOBAL_CONFIG = {
#ifdef WRITE_LOG_FILE
            .DATA_FILE_NAME = PLOTDATA_FILE_NAME,
#endif
            .NUM_OF_ITERATION = NUMBER_OF_ITERATIONS,
            .RUNTIME = RUNTIME_PHASE,
            .WARMUP_TIME = WARMUP_PHASE,
            .NUM_OF_WTHREADS = WWTHREAD_NUM
#ifdef CUSTOM_SHA256_TEST
            ,
            .HASH256_LEN = SHA_INPUT_LEN
#endif

#if  defined(RSA_KEY_GEN) || defined(RSA_CRYPTO_TEST) || defined(RSA_SIGN_TEST)
            ,
            .RSA_BITS_MULTIPLICATOR = DEFAULT_RSA_BITS
#endif

#if defined(SGX_ENCRYPTO_TEST) || defined(SGX_DECRYPTO_TEST) || defined(SGX_DECRYPTO_EXT_TEST) || defined(SGX_DECRYPTO_ENCRYPTO) || defined(AEAD_AES256GCM_ENCRYPT_TEST) || defined(AEAD_AES256GCM_DECRYPT_TEST)
            ,
            .CRYPTO_BUFLEN = CRYPTO_BUF_LEN
#endif


#if defined(RSA_CRYPTO_TEST) || defined(RSA_SIGN_TEST)
            ,
            .RSA_MESSAGE_LEN = RSA_MSG_LEN 
#endif

#ifdef DNA_PATTERN_MATCHING
            ,
            .DNA_INPUT = INPUT_DNA,
            .PATTERN_INPUT = PATTERN,
            .SHOW_DIST = DIST_FLAG,
            .SHOW_POS = SHOW_POS_FLAG,
            .SHOW_LINE = SHOW_LINE_FLAG,
            .PRINT_LINE = PRINT_LINE_FLAG,
            .MATCH_ONLY = MATCH_ONLY_FLAG,
            .COUNT = COUNT_FLAG,
            .COMPACT = COMPACT_FLAG,
            .DIST = DIST_FLAG,
            .VERBOSE = VERBOSE_FLAG,
            .END_LINE = END_LINE_FLAG,
            .PREFIX = PREFIX_FLAG,
            .INVERT = INVERT_FLAG,
            .BEST = BEST_FLAG,
            .NON_DNA = NON_DNA_FLAG,
            .ALL = ALL_FLAG,
            .MEMORY = (size_t)MEMORY_ARG

#endif

#ifdef EXCEED_EPC_TEST_RAND
            ,
            .READ_BUFLEN = READ_BUF_LEN

#endif
    };

#endif




#endif
