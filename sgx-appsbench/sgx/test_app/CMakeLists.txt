########################## Usefull Cmake Macros ##########################
macro(check_add_definition VARNAME VALUE)
    if(${VARNAME})
        add_definitions(-D${VALUE})        # Checks if the VARNAME IS ON and then add the VALUE as compiler variable
    endif()
endmacro()

macro(check_and_increment_counter TESTVAR COUNTER)
    if(${TESTVAR})
        MATH(EXPR ${COUNTER} "${${COUNTER}}+1")  # Used to count the number of modules to be tested
    endif()
endmacro()


########################## Global Settings ##########################
set(Global_Variables_Path		    "${CMAKE_CURRENT_SOURCE_DIR}/GlobalVariables")
set(COMMON_HEADERS_PATH             "${CMAKE_CURRENT_SOURCE_DIR}/CommonHeaders")

##ToDo refine this and add another variable that includes only the chosen modules and both should be added below the include global and test variables
set(COMMON_TEST_HEADERS             ${CMAKE_CURRENT_SOURCE_DIR}/commonTestFiles/testHeaders ${CMAKE_CURRENT_SOURCE_DIR}/commonTestFiles/seeq)
set(COMMON_TEST_SOURCES             ${CMAKE_CURRENT_SOURCE_DIR}/commonTestFiles/testSources/*.c)
##

set(Utils_Path		                "${CMAKE_CURRENT_SOURCE_DIR}/Utils")
set(Security_Link_Flags			    "-Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -pie")

if (SGX_MODE STREQUAL HW)
    set(ENCLAVE_LIB_NAME            TestEnclave)
    set(APP_NAME                    BenchApp)
    set(SIGNED_ENCLAVE_NAME         TestEnclave.signed.so)
    add_definitions(-DTESTENCLAVE_FILENAME="${SIGNED_ENCLAVE_NAME}")
else()  ##Simulation Mode
    set(ENCLAVE_LIB_NAME            TestEnclaveSim)
    set(APP_NAME                    BenchAppSim)
    set(SIGNED_ENCLAVE_NAME         TestEnclaveSim.signed.so)
    add_definitions(-DTESTENCLAVE_FILENAME="${SIGNED_ENCLAVE_NAME}")
endif()

########################## Inlcude the Globale and Test Variables ##########################
include(cmake/GlobalVariables.cmake)
include(cmake/TestVariables.cmake)


########################## Build The Untrusted SGX-SDK Part ##########################
add_subdirectory(SGX-SDK/app)

########################## Build the Trusted SGX-SDK Part ##########################
add_subdirectory(SGX-SDK/enclave)


########################## Build Open Enclave SDK Part #########################
if (OPEN_ENCLAVE_ENABLE)
    find_package(OpenEnclave CONFIG REQUIRED)
    set(ENCL_DIR             "${CMAKE_CURRENT_SOURCE_DIR}/OpenEnclaveSDK/OEenclave")

    ####### Open Enclave Trusted Part #######
    add_subdirectory(OpenEnclaveSDK/OEapp)

    ####### Open Enclave Untrusted Part #######
    add_subdirectory(OpenEnclaveSDK/OEenclave)

endif()





########################## Build the Baseline Part ##########################
set(BASE_APP_NAME                        BaselineApp)
set(BASELINE_APP_PATH                    ${CMAKE_BINARY_DIR}/${BASE_APP_NAME})

#if(NOT EXISTS ${BASELINE_APP_PATH})   ### TODO: add a cached variable that changes its value to true upon module selection changes and recompiles the baseline only then otherwise the baselines compilation could be skipped other idea is to compile 3 parts at the same time baseline sgx in hardware and simulated mode
    add_subdirectory(baseline)
#endif()