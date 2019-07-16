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


########################## Build The Untrusted Part ##########################
add_subdirectory(app)

########################## Build the Trusted Part ##########################
add_subdirectory(enclave)


