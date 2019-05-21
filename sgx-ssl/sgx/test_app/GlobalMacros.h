#ifndef _GLOBAL_MACROS_
#define _GLOBAL_MACROS_
/*
 * This is more or less a configuration file for the benchmarking tool. Here you can choose your desired options,
 * features and global variable
 */

/*  Debug Options   */
//#define PRINT_CHECKS   //ToDo: This is for debugging and ocall_print_out checks


/*  Available Features   */
//#define WITH_ITERATION_QUERY


/*  Global Values  */
#define NUMBER_OF_ITERATIONS  10//ToDo: This is




/* Global Conditions */
#if defined WITH_ITERATION_QUERY && NUMBER_OF_ITERATIONS
#error "Choose either the interactive approach or the fixed one"
#endif

#endif