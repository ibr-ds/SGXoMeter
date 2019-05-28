#ifndef _TEST_MACROS_
#define _TEST_MACROS_



/*  Available Benchmark Tests  */

//#define RSA_KEY_GEN
//#define ELLIPTIC_CURVE_KEY_GEN
//#define RSA_TESTS
//#define ELLIPTIC_CURVE_TESTS
/*#define ELLIPTIC_CURVE_DIFFIE_HELLMAN_TESTS
#define ELLIPTIC_CURVE_DSA_TESTS
#define BN_TESTS
#define DEFFIE_HELLMAN_TESTS
#define SECURE_HASH_ALGORITHM_256
#define SECURE_HASH_ALGORITHM_1
#define THREAD_TESTS                        */
#define DNA_PATTERN_MATCHING
//#define CUSTOM_TEST                 //ToDo: the idea is to add new custom method that looks like void customTest(int paraCount, void args...); where its like an interface for



/*   DNA Test Flags & Logical Conditions   */

#ifdef DNA_PATTERN_MATCHING
    /*   The checked pattern     */

    #define PATTERN         "CAT"

    /*   The checked DNA with the given pattern       */
    #define INPUT_DNA       "ACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCTCGT\n"\
                            "ACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCATCA\n"\
                            "                       CATGTTACAAATAAAGCAATAGCATCA\n"\
                            "CATGTTACAAA                       TAAAGCAATAGCATCA\n"\
                            "CATOGTTACAAATAAAGCAATAGCATCA\n"\
                            "ACCTCGTAAAAGCTATAGACTTG"

    #define INPUT_DNA_SIZE sizeof(INPUT_DNA)

    #define COUNT_FLAG		1       //Returns only the count of matching lines. When specified, all other options are ignored
    #define SHOW_DIST_FLAG 	1       //Shows the Levenshtein distance of the match
    #define SHOW_POS_FLAG	1       //Shows the position of the match in the text
    #define MATCH_ONLY_FLAG	1       //Print the matching text instead of the whole line
    #define SHOW_LINE_FLAG	1       //Shows the line number of the match
    #define INVERT_FLAG		1       //Returns the non-matching lines. When specified, all other options except 'lines' and 'count', are ignored
    #define COMPACT_FLAG	1       //Uses compact output format
    #define DIST_FLAG		1       //Defines the maximum Levenshtein distance for pattern matching. Default is 0. It should be a positive integer if set
    #define VERBOSE_FLAG	0       //Verbose. Prints verbose information to the standard error channel.
    #define END_LINE_FLAG	1       //Prints only the last part of the matched lines, starting after (not including) the matched part.
    #define PREFIX_FLAG		1       //Prints only the beginning of the matched lines, ending before (not including) the matched part.
    #define BEST_FLAG		1       //Forces seeq to find the best matching position of each line
    #define NON_DNA_FLAG	1       //can be set from this Intervall [0,2]. 0) - Skip line. 1) - Convert character to 'N' (mismatch). 2) - Ignore character.
    #define MEMORY_FLAG		1       //Sets the DFA memory limit (in MB). Default is 0 (unlimited)
    #define ALL_FLAG		1       //Returns all the matching positions of each line
    #define PRINT_LINE_FLAG	1       //Does not print the matched line

    #if  COUNT_FLAG == 0
    #define MASK_COUNT		1
    #else
    #define MASK_COUNT 		0
    #endif

    #if INVERT_FLAG == 0
    #define MASK_INV 		1*MASK_COUNT
    #else
    #define MASK_INV		0*MASK_COUNT
    #endif

    #define MEMORY_ARG		(size_t)MEMORY_FLAG*1024*1024

    /*  DNA TEST LOGICAL CONDITIONS   */
    #if (!defined PRINT_LINE_FLAG || PRINT_LINE_FLAG == 0) && (!defined MATCH_ONLY_FLAG || MATCH_ONLY_FLAG == 0) && (!defined END_LINE_FLAG || END_LINE_FLAG == 0) && (!defined PREFIX_FLAG || PREFIX_FLAG == 0)
    #define PRINT_LINE_FLAG 1
    #endif
	
    #if !defined SHOW_DIST_FLAG && !defined SHOW_POS_FLAG && !defined PRINT_LINE_FLAG && !defined SHOW_LINE_FLAG && !defined COUNT_FLAG && !defined COMPACT_FLAG && !defined PREFIX_FLAG && !defined END_LINE_FLAG
    #error "Invalid options: no output will be generated"
    #endif

    #if defined DIST_FLAG && DIST_FLAG < 0
    #error "The distance should be positive Integer if defined"
    #endif
#endif


#endif
