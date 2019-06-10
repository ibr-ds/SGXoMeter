########################## Available Benchmark Tests/Modules ##########################

set(RSA_KEY_GEN_MODULE					NO CACHE BOOL "YES OR NO for RSA key generation tests")
check_add_definition(RSA_KEY_GEN_MODULE			RSA_KEY_GEN)

set(EC_KEY_GEN_MODULE					NO CACHE BOOL "YES OR NO for elliptic curve Key generation tests")
check_add_definition(EC_KEY_GEN_MODULE			ELLIPTIC_CURVE_KEY_GEN)

set(RSA_TESTS_MODULE					NO CACHE BOOL "YES OR NO for multiple RSA tests")
check_add_definition(RSA_TESTS_MODULE 			RSA_TESTS)
	
set(EC_TESTS_MODULE					NO CACHE BOOL "YES OR NO for multiple elliptic curve tests")
check_add_definition(EC_TESTS_MODULE			ELLIPTIC_CURVE_TESTS)
	
set(EC_DH_TESTS_MODULE					NO CACHE BOOL "YES OR NO for elliptic curve deffie hellman tests")
check_add_definition(EC_DH_TESTS_MODULE 		ELLIPTIC_CURVE_DIFFIE_HELLMAN_TESTS)

set(EC_DSA_TESTS_MODULE					NO CACHE BOOL "YES OR NO for elliptic curve and digital signature algorithm tests")
check_add_definition(EC_DSA_TESTS_MODULE 		ELLIPTIC_CURVE_DSA_TESTS)

set(BN_TESTS_MODULE					NO CACHE BOOL "YES OR NO for openssl BN-tests")
check_add_definition(BN_TESTS_MODULE	 		BN_TESTS)
	
set(DH_TESTS_MODULE					NO CACHE BOOL "YES OR NO for deffie hellman tests")
check_add_definition(DH_TESTS_MODULE	 		DEFFIE_HELLMAN_TESTS)

set(SHA_256_MODULE					NO CACHE BOOL "YES OR NO for secure hash algorithm 256 tests")
check_add_definition(SHA_256_MODULE	 		SECURE_HASH_ALGORITHM_256)

set(SHA1_MODULE						NO CACHE BOOL "YES OR NO for secure hash algorithm 1 tests")
check_add_definition(SHA1_MODULE			SECURE_HASH_ALGORITHM_1)

set(THREAD_TESTS_MODULE					NO CACHE BOOL "YES OR NO for sgx multi-threading tests")
check_add_definition(THREAD_TESTS_MODULE 		THREAD_TESTS)

set(DNA_PATTERN_MATCHING_MODULE				NO CACHE BOOL "YES OR NO for DNA Pattern Matching tests")
check_add_definition(DNA_PATTERN_MATCHING_MODULE 	DNA_PATTERN_MATCHING)

set(CUSTOM_TEST_MODULE					NO CACHE BOOL "YES OR NO to enable the custom test module")
check_add_definition(CUSTOM_TEST_MODULE 		CUSTOM_TEST)
		

########################## DNA Pattern Module Configuration ##########################
if(RUNTIME_PARSER_FEATURE AND DNA_PATTERN_MATCHING_MODULE)
	message("Building with the DNA Pattern module. The parameter/flags should be entered manually and parsed while runtime or the standard values will be applied. Consider using the formats from seeq repository")
else()
	if(DNA_PATTERN_MATCHING_MODULE)	
		message("Building with the DNA Pattern module. The parameter/flags should be entered manually and parsed while compile or the standard values will be applied. Consider using cmake-gui")
		set(PATTERN_VALUE				"ACT" CACHE STRING "The searched Pattern in the DNA")
		string(LENGTH PATTERN_VALUE PATTERN_LENGTH)

		set(INPUT_DNA_VALUE				"ACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCTCGT\n
ACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCATCA\n
	   	       CATGTTACAAATAAAGCAATAGCATCA\n
CATGTTACAAA                       TAAAGCAATAGCATCA\n
	              CATOGTTACAAATAAAGCAATAGCATCA\n
ACCTCGTAAAAGCTATAGACTTG" CACHE STRING "The required DNA sequence for the search/matching")

		add_definitions(-DPATTERN=${PATTERN_VALUE} -DINPUT_DNA=${INPUT_DNA_VALUE} -DINPUT_DNA_SIZE=sizeof(INPUT_DNA))
		
		set(COUNT_FLAG_VALUE				0 CACHE STRING "0 or 1. Returns only the count of matching lines. If enabled all other options will be ignored")
		set(SHOW_DIST_FLAG_VALUE			0 CACHE STRING "0 or 1. Shows the Levenshtein distance of the match")
		set(SHOW_POS_FLAG_VALUE				0 CACHE STRING "0 or 1. Shows the position of the match in the text")
		set(MATCH_ONLY_FLAG_VALUE			0 CACHE STRING "0 or 1. Print the matching text instead of the whole line")
		set(SHOW_LINE_FLAG_VALUE			0 CACHE STRING "0 or 1. Shows the line number of the match")
		set(INVERT_FLAG_VALUE				0 CACHE STRING "0 or 1. Returns the non-matching lines. When specified, all other options except 'lines' and 'count', are ignored")
		set(COMPACT_FLAG_VALUE				0 CACHE STRING "0 or 1. Uses compact output format")
		set(DIST_FLAG_VALUE				0 CACHE STRING "[0.. < length PATTERN_VALUE]. Defines the maximum Levenshtein distance for pattern matching. It should be a positive integer if set")
		set(VERBOSE_FLAG_VALUE				0 CACHE STRING "0 or 1. Verbose. Prints verbose information to the standard error channel.")
		set(END_LINE_FLAG_VALUE				0 CACHE STRING "0 or 1. Prints only the last part of the matched lines, starting after (not including) the matched part.")
		set(PREFIX_FLAG_VALUE				0 CACHE STRING "0 or 1. Prints only the beginning of the matched lines, ending before (not including) the matched part.")
		set(BEST_FLAG_VALUE				0 CACHE STRING "0 or 1. Forces seeq to find the best matching position of each line")
		set(NON_DNA_FLAG_VALUE				0 CACHE STRING "Can be set from this Intervall [0,2]. 0) - Skip line. 1) - Convert character to 'N' (mismatch). 2) - Ignore character.")
		set(MEMORY_FLAG_VALUE				0 CACHE STRING "Sets the DFA memory limit (in MB). Default is 0 (unlimited)")
		set(ALL_FLAG_VALUE				0 CACHE STRING "Returns all the matching positions of each line")
		set(PRINT_LINE_FLAG_VALUE			0 CACHE STRING "Does not print the matched line")
		
		if(COUNT_FLAG_VALUE EQUAL 0)
			set(MASK_COUNT_VALUE			1)
		else()
			set(MASK_COUNT_VALUE			0)
		endif()

		if(INVERT_FLAG_VALUE EQUAL 0)
			set(MASK_INV_VALUE			1*${MASK_COUNT_VALUE})
		else()
			set(MASK_INV_VALUE			0*${MASK_COUNT_VALUE})
		endif()

		########################## DNA TEST LOGICAL CONDITIONS ##########################
		
		if((PRINT_LINE_FLAG_VALUE EQUAL 0) AND (MATCH_ONLY_FLAG_VALUE EQUAL 0) AND (END_LINE_FLAG_VALUE EQUAL 0) AND (PREFIX_FLAG_VALUE EQUAL 0))
			set(PRINT_LINE_FLAG_VALUE 		1)
		endif()

		if((SHOW_DIST_FLAG_VALUE EQUAL 0) AND (SHOW_POS_FLAG_VALUE EQUAL 0) AND (PRINT_LINE_FLAG_VALUE EQUAL 0) AND (SHOW_LINE_FLAG_VALUE EQUAL 0) 
		   AND (COUNT_FLAG_VALUE EQUAL 0) AND (COMPACT_FLAG_VALUE  EQUAL 0) AND (PREFIX_FLAG_VALUE     EQUAL 0) AND (END_LINE_FLAG_VALUE  EQUAL 0))
		   	message(FATAL_ERROR "ERROR: Invalid options: no output will be generated. Please reconfigure the variables correctly")
		endif()
		
		if(DIST_FLAG_VALUE LESS 0 OR DIST_FLAG_VALUE GREATER ${PATTERN_LENGTH}-2) # -2 because of the ""
			message(FATAL_ERROR "ERROR the distance should be positive number and less than the patterns length!!")
		endif()

		########################## Add the compiler variable definitions with their values ##########################

		add_definitions(-DCOUNT_FLAG=${COUNT_FLAG_VALUE})
		add_definitions(-DSHOW_DIST_FLAG=${SHOW_DIST_FLAG_VALUE})
		add_definitions(-DSHOW_POS_FLAG=${SHOW_POS_FLAG_VALUE})
		add_definitions(-DMATCH_ONLY_FLAG=${MATCH_ONLY_FLAG_VALUE})
		add_definitions(-DSHOW_LINE_FLAG=${SHOW_LINE_FLAG_VALUE})
		add_definitions(-DINVERT_FLAG=${INVERT_FLAG_VALUE})
		add_definitions(-DCOMPACT_FLAG=${COMPACT_FLAG_VALUE})
		add_definitions(-DDIST_FLAG=${DIST_FLAG_VALUE})
		add_definitions(-DVERBOSE_FLAG=${VERBOSE_FLAG_VALUE})
		add_definitions(-DEND_LINE_FLAG=${END_LINE_FLAG_VALUE})
		add_definitions(-DPREFIX_FLAG=${PREFIX_FLAG_VALUE})
		add_definitions(-DBEST_FLAG=${BEST_FLAG_VALUE})
		add_definitions(-DNON_DNA_FLAG=${NON_DNA_FLAG_VALUE})
		add_definitions(-DMEMORY_FLAG=${MEMORY_FLAG_VALUE})
		add_definitions(-DALL_FLAG=${ALL_FLAG_VALUE})
		add_definitions(-DPRINT_LINE_FLAG=${PRINT_LINE_FLAG_VALUE})
		add_definitions(-DMASK_COUNT=${MASK_COUNT_VALUE})
		add_definitions(-DMASK_INV=${MASK_INV_VALUE})
		add_definitions(-DMEMORY_ARG=\(size_t\)${MEMORY_FLAG}*1024*1024)
	endif()
endif()



