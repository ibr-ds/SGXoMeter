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
#define WRITE_LOG_FILE


/*  Global Values  */
#define PLOTDATA_FILE_NAME "plotdata.txt"
#define NUMBER_OF_ITERATIONS  10 //ToDo: This will be done later in cmake
#define CYCLES_RATE 1000000 //ToDo: This should also be done in cmake later
#define ARRAY_SIZE (1000000)



/*  Global Conditions */
#if defined WITH_ITERATION_QUERY && NUMBER_OF_ITERATIONS
#error "Choose either the interactive approach or the fixed one"
#endif

#if !defined WRITE_LOG_FILE
#undef PLOTDATA_FILE_NAME
#endif


#endif
