#include "GlobalMacros.h" //ToDo delete this later as this will be obselete through the CMAKELISTS.txt

#ifndef _GLOBAL_VARIABLES_
#define _GLOBAL_VARIABLES_

#include <stdint.h>                         // Macros will be set  else where

#ifdef RUNTIME_PARSER
    #ifdef WRITE_LOG_FILE
    extern char *DATA_FILE_NAME;// = PLOTDATA_FILE_NAME;
    #endif

    extern int NUM_OF_ITERATION; // = NUMBER_OF_ITERATIONS; //WILL BE USED
    extern uint64_t ARR_SIZE; // = ARRAY_SIZE;
    extern uint64_t RATE; // = CYCLES_RATE;

#else
    #ifdef WRITE_LOG_FILE
    char *DATA_FILE_NAME = PLOTDATA_FILE_NAME;
    #endif

    int NUM_OF_ITERATION = NUMBER_OF_ITERATIONS; //WILL BE USED
    uint64_t ARR_SIZE = ARRAY_SIZE;
    uint64_t RATE = CYCLES_RATE;
#endif

#endif