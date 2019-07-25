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

#ifdef CUSTOM_SHA256_TEST
    size_t HASH256_LEN;
#endif

#ifdef RSA_KEY_GEN
    int RSA_BITS;
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

} globalConfig_t;




#endif
