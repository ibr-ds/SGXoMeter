########################## Available Benchmark Tests/Modules ##########################

set(MODULE_RSA_KEY_GEN					NO CACHE BOOL "YES OR NO for RSA key generation tests")
check_add_definition(MODULE_RSA_KEY_GEN			RSA_KEY_GEN)

set(MODULE_EC_KEY_GEN					NO CACHE BOOL "YES OR NO for elliptic curve Key generation tests")
check_add_definition(MODULE_EC_KEY_GEN			ELLIPTIC_CURVE_KEY_GEN)

set(MODULE_RSA_TESTS					NO CACHE BOOL "YES OR NO for multiple RSA tests")
check_add_definition(MODULE_RSA_TESTS 			RSA_TESTS)
	
set(MODULE_EC_TESTS					NO CACHE BOOL "YES OR NO for multiple elliptic curve tests")
check_add_definition(MODULE_EC_TESTS			ELLIPTIC_CURVE_TESTS)
	
set(MODULE_EC_DH_TESTS					NO CACHE BOOL "YES OR NO for elliptic curve deffie hellman tests")
check_add_definition(MODULE_EC_DH_TESTS 		ELLIPTIC_CURVE_DIFFIE_HELLMAN_TESTS)

set(MODULE_EC_DSA_TESTS					NO CACHE BOOL "YES OR NO for elliptic curve and digital signature algorithm tests")
check_add_definition(MODULE_EC_DSA_TESTS 		ELLIPTIC_CURVE_DSA_TESTS)

set(MODULE_BN_TESTS					NO CACHE BOOL "YES OR NO for openssl BN-tests")
check_add_definition(MODULE_BN_TESTS	 		BN_TESTS)
	
set(MODULE_DH_TESTS					NO CACHE BOOL "YES OR NO for deffie hellman tests")
check_add_definition(MODULE_DH_TESTS	 		DEFFIE_HELLMAN_TESTS)

set(MODULE_SHA_256					NO CACHE BOOL "YES OR NO for secure hash algorithm 256 tests")
check_add_definition(MODULE_SHA_256	 		SECURE_HASH_ALGORITHM_256)

set(MODULE_SHA1						NO CACHE BOOL "YES OR NO for secure hash algorithm 1 tests")
check_add_definition(MODULE_SHA1			SECURE_HASH_ALGORITHM_1)

set(MODULE_THREAD_TESTS					NO CACHE BOOL "YES OR NO for sgx multi-threading tests")
check_add_definition(MODULE_THREAD_TESTS 		THREAD_TESTS)

set(MODULE_DNA_PATTERN_MATCHING				NO CACHE BOOL "YES OR NO for DNA Pattern Matching tests")
check_add_definition(MODULE_DNA_PATTERN_MATCHING 	DNA_PATTERN_MATCHING)

set(MODULE_CUSTOM_TEST					NO CACHE BOOL "YES OR NO to enable the custom test module")
check_add_definition(MODULE_CUSTOM_TEST 		CUSTOM_TEST)
		

########################## DNA Pattern Module Configuration ##########################
if(FEATURE_RUNTIME_PARSER AND MODULE_DNA_PATTERN_MATCHING)
	message(STATUS "Building with the DNA Pattern module. The parameter/flags should be entered manually and parsed while runtime or the standard values will be applied. Consider using the formats from seeq repository")
else()
	message(STATUS "Building with the DNA Pattern module. The parameter/flags should be entered manually and parsed while compile or the standard values will be applied. Consider using cmake-gui")
endif()
if(MODULE_DNA_PATTERN_MATCHING)
	set(VALUE_PATTERN				"ACT" CACHE STRING "The searched Pattern in the DNA")
	string(LENGTH VALUE_PATTERN PATTERN_LENGTH)

	set(VALUE_INPUT_DNA				"ACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCTCGT\\nACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCATCA\\n   	       CATGTTACAAATAAAGCAATAGCATCA\\nCATGTTACAAA                       TAAAGCAATAGCATCA\\n              CATOGTTACAAATAAAGCAATAGCATCA\\nACCTCGTAAAAGCTATAGACTTG" CACHE STRING "The required DNA sequence for the search/matching")

	add_definitions(-DPATTERN="${VALUE_PATTERN}" -DINPUT_DNA="${VALUE_INPUT_DNA}" -DINPUT_DNA_SIZE=sizeof\(INPUT_DNA\))
	
	set(VALUE_COUNT_FLAG					0 CACHE STRING "0 or 1. Returns only the count of matching lines. If enabled all other options will be ignored")
	set(VALUE_SHOW_DIST_FLAG				0 CACHE STRING "0 or 1. Shows the Levenshtein distance of the match")
	set(VALUE_SHOW_POS_FLAG					0 CACHE STRING "0 or 1. Shows the position of the match in the text")
	set(VALUE_MATCH_ONLY_FLAG				0 CACHE STRING "0 or 1. Print the matching text instead of the whole line")
	set(VALUE_SHOW_LINE_FLAG				0 CACHE STRING "0 or 1. Shows the line number of the match")
	set(VALUE_INVERT_FLAG					0 CACHE STRING "0 or 1. Returns the non-matching lines. When specified, all other options except 'lines' and 'count', are ignored")
	set(VALUE_COMPACT_FLAG					0 CACHE STRING "0 or 1. Uses compact output format")
	set(VALUE_DIST_FLAG						0 CACHE STRING "[0.. < length PATTERN_VALUE]. Defines the maximum Levenshtein distance for pattern matching. It should be a positive integer if set")
	set(VALUE_VERBOSE_FLAG					0 CACHE STRING "0 or 1. Verbose. Prints verbose information to the standard error channel.")
	set(VALUE_END_LINE_FLAG					0 CACHE STRING "0 or 1. Prints only the last part of the matched lines, starting after (not including) the matched part.")
	set(VALUE_PREFIX_FLAG					0 CACHE STRING "0 or 1. Prints only the beginning of the matched lines, ending before (not including) the matched part.")
	set(VALUE_BEST_FLAG						0 CACHE STRING "0 or 1. Forces seeq to find the best matching position of each line")
	set(VALUE_NON_DNA_FLAG					0 CACHE STRING "Can be set from this Intervall [0,2]. 0) - Skip line. 1) - Convert character to 'N' (mismatch). 2) - Ignore character.")
	set(VALUE_MEMORY_FLAG					0 CACHE STRING "Sets the DFA memory limit (in MB). Default is 0 (unlimited)")
	set(VALUE_ALL_FLAG						0 CACHE STRING "Returns all the matching positions of each line")
	set(VALUE_PRINT_LINE_FLAG				0 CACHE STRING "Does not print the matched line")
	
	if(VALUE_COUNT_FLAG EQUAL 0)
		set(VALUE_MASK_COUNT				1)
	else()
		set(VALUE_MASK_COUNT				0)
	endif()

	if(VALUE_INVERT_FLAG EQUAL 0)
		set(VALUE_MASK_INV			1*${VALUE_MASK_COUNT})
	else()
		set(VALUE_MASK_INV			0*${VALUE_MASK_COUNT})
	endif()

	########################## DNA TEST LOGICAL CONDITIONS ##########################
	
	if((VALUE_PRINT_LINE_FLAG EQUAL 0) AND (VALUE_MATCH_ONLY_FLAG EQUAL 0) AND (VALUE_END_LINE_FLAG EQUAL 0) AND (VALUE_PREFIX_FLAG EQUAL 0))
		set(VALUE_PRINT_LINE_FLAG	 		1)
	endif()

	if((VALUE_SHOW_DIST_FLAG EQUAL 0) AND (VALUE_SHOW_POS_FLAG EQUAL 0) AND (VALUE_PRINT_LINE_FLAG EQUAL 0) AND (VALUE_SHOW_LINE_FLAG EQUAL 0)
	   AND (VALUE_COUNT_FLAG EQUAL 0) AND (VALUE_COMPACT_FLAG  EQUAL 0) AND (VALUE_PREFIX_FLAG     EQUAL 0) AND (VALUE_END_LINE_FLAG  EQUAL 0))
	   	message(FATAL_ERROR "ERROR: Invalid options: no output will be generated. Please reconfigure the variables correctly")
	endif()
	
	if(VALUE_DIST_FLAG LESS 0 OR VALUE_DIST_FLAG GREATER ${PATTERN_LENGTH}-2) # -2 because of the ""
		message(FATAL_ERROR "ERROR the distance should be positive number and less than the patterns length!!")
	endif()

	########################## Add the compiler variable definitions with their values ##########################

	add_definitions(-DCOUNT_FLAG=${VALUE_COUNT_FLAG})
	add_definitions(-DSHOW_DIST_FLAG=${VALUE_SHOW_DIST_FLAG})
	add_definitions(-DSHOW_POS_FLAG=${VALUE_SHOW_POS_FLAG})
	add_definitions(-DMATCH_ONLY_FLAG=${VALUE_MATCH_ONLY_FLAG})
	add_definitions(-DSHOW_LINE_FLAG=${VALUE_SHOW_LINE_FLAG})
	add_definitions(-DINVERT_FLAG=${VALUE_INVERT_FLAG})
	add_definitions(-DCOMPACT_FLAG=${VALUE_COMPACT_FLAG})
	add_definitions(-DDIST_FLAG=${VALUE_DIST_FLAG})
	add_definitions(-DVERBOSE_FLAG=${VALUE_VERBOSE_FLAG})
	add_definitions(-DEND_LINE_FLAG=${VALUE_END_LINE_FLAG})
	add_definitions(-DPREFIX_FLAG=${VALUE_PREFIX_FLAG})
	add_definitions(-DBEST_FLAG=${VALUE_BEST_FLAG})
	add_definitions(-DNON_DNA_FLAG=${VALUE_NON_DNA_FLAG})
	add_definitions(-DMEMORY_FLAG=${VALUE_MEMORY_FLAG})
	add_definitions(-DALL_FLAG=${VALUE_ALL_FLAG})
	add_definitions(-DPRINT_LINE_FLAG=${VALUE_PRINT_LINE_FLAG})
	add_definitions(-DMASK_COUNT=${VALUE_MASK_COUNT})
	add_definitions(-DMASK_INV=${VALUE_MASK_INV})
	add_definitions(-DMEMORY_ARG=${VALUE_MEMORY_FLAG}*1024*1024)
endif()




