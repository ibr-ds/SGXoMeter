########################## This is more or less a configuration fileww for the benchmarking tool ##########################



########################## Debug Options ##########################
set(PRINT_CHECKS_DEBUG			NO CACHE BOOL "YES OR NO for print out debug")
check_add_definition(PRINT_CHECKS_DEBUG PRINT_CHECKS)

########################## Available Features ##########################

set(FEATURE_LOGGING_FILE		YES CACHE BOOL "YES OR NO for logging results to an external file")
check_add_definition(FEATURE_LOGGING_FILE 					WRITE_LOG_FILE)

set(FEATURE_MEMSET_SGX_EXTRA_CODE		NO CACHE BOOL "YES OR NO for memset code for sgx")
check_add_definition(FEATURE_MEMSET_SGX_EXTRA_CODE 			MEMSET_SGX)

set(FEATURE_RUNTIME_PARSER		YES CACHE BOOL "YES OR NO for getting the global and test variables in runtime")
check_add_definition(FEATURE_RUNTIME_PARSER 				RUNTIME_PARSER)
if(FEATURE_RUNTIME_PARSER)
	message(STATUS "Building the benchmarking tool with runtime parser. You can set the global/test variables manually or they will be set to the standard values")
endif()

########################## Global Variables with Values ##########################
if(FEATURE_LOGGING_FILE)
	set(GLOB_RESULT_FILE_NAME		"plotdata.txt" CACHE STRING "name of the output results file")
	add_definitions(-DPLOTDATA_FILE_NAME="${GLOB_RESULT_FILE_NAME}")
endif()

set(GLOB_NUM_OF_ITERATIONS		0 CACHE STRING "Sets number of iterations. 0 is for unlimited looping")
if(GLOB_NUM_OF_ITERATIONS GREATER -1)
	add_definitions(-DNUMBER_OF_ITERATIONS=${GLOB_NUM_OF_ITERATIONS})
else()
	message(FATAL_ERROR "Invalid Number of iterations. Please reconfigure again with the correct value")
endif()

set(GLOB_CYCLES_RATE_VALUE			1000000 CACHE STRING "Sets the number of cycles rate for the benchmark")
if(GLOB_CYCLES_RATE_VALUE GREATER 0)
	add_definitions(-DCYCLES_RATE=${GLOB_CYCLES_RATE_VALUE})
else()
	message(FATAL_ERROR "Invalid cycles rate value!. Please reconfigure again with correct values")
endif()

set(GLOB_ARRAY_SIZE_VALUE			1000000 CACHE STRING "Sets the size of the array that contains the results")
if(GLOB_ARRAY_SIZE_VALUE GREATER 0)
	add_definitions(-DARRAY_SIZE=${GLOB_ARRAY_SIZE_VALUE})
else()
	message(FATAL_ERROR "Invalid Array size!. Please reconfigure again with correct values")
endif()








