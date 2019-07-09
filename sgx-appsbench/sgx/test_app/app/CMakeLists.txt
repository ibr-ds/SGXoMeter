
if(DEBUG) 
    set(SGX_COMMON_CFLAGS 	"${SGX_COMMON_CFLAGS} -O0 -g")
    set(SgxSSK_LINK_LIB		"sgx_usgxssld")
else()
    set(SGX_COMMON_CFLAGS 	"${SGX_COMMON_CFLAGS} -O2 -D_FORTIFY_SOURCE=2")
    set(SgxSSK_LINK_LIB		"sgx_usgxssl")
endif()

########################## Build Untrusted Part of BenchApp ##########################
set(UNTRUSTED_DIR		    "${CMAKE_CURRENT_SOURCE_DIR}")
set(APP_INCLUDE_PATHS 		 ${UNTRUSTED_DIR} ${SGXSDK_INCLUDE_DIRS} ${Global_Variables_Path})

set(CMAKE_C_FLAGS 		    "${CMAKE_C_FLAGS} ${SGX_COMMON_CFLAGS} -fPIC -fpie -fstack-protector -Wformat -Wformat-security -Wno-attributes")
set(CMAKE_CXX_FLAGS 		"${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11")


set(APP_Link_Flags		    "${SGX_COMMON_CFLAGS} ${Security_Link_Flags} -L${SGXSDK_LIBRARIES} -l${SGX_URTS_LIB} -l${SGX_USVC_LIB} -L${OPENSSL_LIBRARY_PATH} -l${SgxSSK_LINK_LIB} -lpthread")
set(APP_SRC_FILES 		     TestEnclave_u.c InputParser.c TestApp.cpp)

set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        "${UNTRUSTED_DIR}/TestEnclave_u.c"
        "${UNTRUSTED_DIR}/TestEnclave_u.h"
        )

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/TestEnclave_u.c
        COMMAND ${SGX_EDGER8R} --untrusted ../enclave/TestEnclave.edl
        --search-path ../enclave/ # enclave.edl
        --search-path ${SGXSDK_INCLUDE_DIRS} 
        --search-path ${PACKAGE_INC} #sgx_tsgxssl.edl
        COMMENT "Generating TestEnclave_u.{c,h}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${APP_NAME} ${APP_SRC_FILES} TestEnclave_u.c)

set_target_properties(${APP_NAME}
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(${APP_NAME} PRIVATE
        ${APP_INCLUDE_PATHS}
)

target_link_libraries(${APP_NAME}   ${APP_Link_Flags})

add_dependencies(${APP_NAME}        ${ENCLAVE_LIB_NAME})

