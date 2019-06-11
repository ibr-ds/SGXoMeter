
if(DEBUG) 
    set(SGX_COMMON_CFLAGS 	"${SGX_COMMON_CFLAGS} -O0 -g")
    set(SgxSSK_LINK_LIB		"sgx_usgxssld")
else()
    set(SGX_COMMON_CFLAGS 	"${SGX_COMMON_CFLAGS} -O2 -D_FORTIFY_SOURCE=2")
    set(SgxSSK_LINK_LIB		"sgx_usgxssl")
endif()

########################## Build Untrusted Part of BenchApp ##########################
set(UNTRUSTED_DIR		"${CMAKE_CURRENT_SOURCE_DIR}")
set(APP_INCLUDE_PATHS 		"I${UNTRUSTED_DIR} -I${SGXSDK_INCLUDE_DIRS} -I${Global_Variables_Path}")

set(CMAKE_C_FLAGS 		"${CMAKE_C_FLAGS} ${SGX_COMMON_CFLAGS} -fPIC -fpie -fstack-protector -Wformat -Wformat-security -Wno-attributes ${APP_INCLUDE_PATHS}") #try to remove app Include Paths because they are included later
set(CMAKE_CXX_FLAGS 		"${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11")


set(APP_Link_Flags		"${SGX_COMMON_CFLAGS} ${Security_Link_Flags} -L${SGXSDK_LIBRARIES} -l${SGX_URTS_LIB} -l${SGX_USVC_LIB} -L${OPENSSL_LIBRARY_PATH} -l${SgxSSK_LINK_LIB} -lpthread")
set(APP_SRC_FILES 		TestEnclave_u.c InputParser.c TestApp.cpp)

set_directory_properties(PROPERTIES
        ADDITIONAL_MAKE_CLEAN_FILES "TestEnclave_u.c; TestEnclave_u.h")

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/TestEnclave_u.c
        COMMAND ${SGX_EDGER8R} --untrusted ../enclave/TestEnclave.edl
        --search-path ../enclave/ # enclave.edl
        --search-path ${SGXSDK_INCLUDE_DIRS} 
        --search-path ${PACKAGE_INC} #sgx_tsgxssl.edl
        COMMENT "Generating TestEnclave_u.{c,h}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(BenchApp ${APP_SRC_FILES} TestEnclave_u.c)

target_include_directories(BenchApp PRIVATE
        ${SGXSDK_INCLUDE_DIRS}  
	${UNTRUSTED_DIR}
        ${Global_Variables_Path}
)

target_link_libraries(BenchApp	   ${APP_Link_Flags})

add_dependencies(BenchApp TestEnclave)

