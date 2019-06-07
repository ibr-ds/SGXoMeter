########################## This is more or less a configuration fileww for the benchmarking tool ##########################



########################## Debug Options ##########################
set(PRINT_CHECKS_DEBUG			NO CACHE BOOL "YES OR NO for print out debug")
check_add_definition(PRINT_CHECKS_DEBUG PRINT_CHECKS)

########################## Available Features ##########################

set(LOGGING_FILE_FEATURE		YES CACHE BOOL "YES OR NO for logging results to an external file")
check_add_definition(LOGGING_FILE_FEATURE WRITE_LOG_FILE)

set(MEMSET_SGX_EXTRA_CODE		NO CACHE BOOL "YES OR NO for memset code for sgx")
check_add_definition(MEMSET_SGX_EXTRA_CODE MEMSET_SGX)

set(RUNTIME_PARSER_FEATURE		YES CACHE BOOL "YES OR NO for getting the global and test variables in runtime")
check_add_definition(RUNTIME_PARSER_FEATURE RUNTIME_PARSER)
if(RUNTIME_PARSER_FEATURE)
	message(STATUS "Building the benchmarking tool with runtime parser. You can set the global/test variables manually or they will be set to the standard values")
endif()

########################## Global Variables with Values ##########################
if(LOGGING_FILE_FEATURE)
	set(RESULT_FILE_NAME		"plotdata.txt" CACHE STRING "name of the output results file")
	add_definitions(-DPLOTDATA_FILE_NAME=${RESULT_FILE_NAME})
endif()

set(NUM_OF_ITERATIONS		0 CACHE STRING "Sets number of iterations. 0 is for unlimited looping")
if(NUM_OF_ITERATIONS GREATER 0)
	add_definitions(-DNUMBER_OF_ITERATIONS=${NUM_OF_ITERATIONS})
endif()

set(CYCLES_RATE_VALUE			1000000 CACHE STRING "Sets the number of cycles rate for the benchmark")
if(CYCLES_RATE_VALUE GREATER 0)
	add_definitions(-DCYCLES_RATE=${CYCLES_RATE_VALUE})
else()
	message(FATAL_ERROR "Invalid cycles rate value!. Please reconfigure again with correct values")
endif()

set(ARRAY_SIZE_VALUE			1000000 CACHE STRING "Sets the size of the array that contains the results")
if(ARRAY_SIZE_VALUE GREATER 0)
	add_definitions(-DARRAY_SIZE=${ARRAY_SIZE_VALUE})
else()
	message(FATAL_ERROR "Invalid Array size!. Please reconfigure again with correct values")
endif()








