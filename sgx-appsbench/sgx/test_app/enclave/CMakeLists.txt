########################## Build Trusted Part of BenchApp ##########################

if(DEBUG) 
    set(SGX_COMMON_CFLAGS 	"${SGX_COMMON_CFLAGS} -O0 -g")
    set(SGXSSL_LIBRARY		"sgx_tsgxssld")
    set(OpenSSL_CRYP_LIBRARY	"sgx_tsgxssl_cryptod")
else()
    set(SGX_COMMON_CFLAGS 	"${SGX_COMMON_CFLAGS} -O2 -D_FORTIFY_SOURCE=2")
    set(SGXSSL_LIBRARY		"sgx_tsgxssl")
    set(OpenSSL_CRYP_LIBRARY	"sgx_tsgxssl_crypto")
endif()


#############ask nico how to implement this ################
#TSETJMP_LIB := -lsgx_tsetjmp     

#ifeq "20" "$(word 1, $(sort 20 $(SGXSDK_INT_VERSION)))"
 #       TSETJMP_LIB:=
#endif


set(ENCLAVE_DIR			".")

file(GLOB Trusted_Cpp_Files
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

file(GLOB Trusted_C_Files
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c"
	"${CMAKE_CURRENT_SOURCE_DIR}/seeq/*.c")

set(Trusted_Include_Paths	"-I.. -I../GlobalVariables -I${ENCLAVE_DIR} -I${SGXSDK_INCLUDE_DIRS} -I${SGXSDK_INCLUDE_DIRS}/tlibc -I${SGX_LIBCXX_PATH} -I${PACKAGE_INC}")



set(SOURCE_FILES		"${Trusted_Cpp_Files} ${Trusted_C_Files}")


set_directory_properties(PROPERTIES
        ADDITIONAL_MAKE_CLEAN_FILES "TestEnclave_t.c; TestEnclave_t.h")

set(Common_C_CPP_FLAGS		"-DOS_ID=${OS_ID} ${SGX_COMMON_CFLAGS} -nostdinc -fvisibility=hidden -fpic -fpie -fstack-protector -fno-builtin-printf -Wformat -Wformat-security ${Trusted_Include_Paths}-include \"tsgxsslio.h\"") ##maybe delete the trusted include paths

set(CMAKE_C_FLAGS 		"${CMAKE_C_FLAGS} ${Common_C_CPP_FLAGS} -Wno-implicit-function-declaration -std=c11")
set(CMAKE_CXX_FLAGS 		"${CMAKE_CXX_FLAGS} ${Common_C_CPP_FLAGS} -std=c++11 -nostdinc++")

set(SgxSSL_LINK_LIB		"-L${OPENSSL_LIBRARY_PATH} -Wl,--whole-archive -l${SGXSSL_LIBRARY} -Wl,--no-whole-archive -l${OpenSSL_CRYP_LIBRARY}")
set(Security_Link_Flags		"-Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now -pie")


add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/TestEnclave_t.c
        COMMAND ${SGX_EDGER8R} --trusted TestEnclave.edl
        --search-path ${SGXSDK_INCLUDE_DIRS}
        --search-path ${PACKAGE_INC} #sgx_tsgxssl.edl	
        COMMENT "Generating Enclave_t.{c,h}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )

add_library(TestEnclave SHARED ${SOURCE_FILES})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../GlobalVariables
	${CMAKE_CURRENT_SOURCE_DIR}/..
	${CMAKE_CURRENT_SOURCE_DIR}        
        ${SGXSDK_INCLUDE_DIRS}
        ${SGXSDK_INCLUDE_DIRS}/tlibc
        ${SGX_LIBCXX_PATH}
	${PACKAGE_INC}
)


set_target_properties(TestEnclave PROPERTIES PREFIX "")  ##maybe remove this

target_link_libraries(TestEnclave "${SGX_COMMON_CFLAGS} \
    -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles \
    ${Security_Link_flags} \
    ${SgxSSL_LINK_LIB} -L${SGX_LIBRARY_PATH} \
    -Wl,--whole-archive -l${SGX_TRTS_LIB} -Wl,--no-whole-archive \
    -Wl,--start-group -lsgx_tstdc -lsgx_tcxx -lsgx_tcrypto -l${SGX_TSVC_LIB} -Wl,--end-group \
    -Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined \
    -Wl,-pie,-eenclave_entry -Wl,--export-dynamic \
    -Wl,--defsym,__ImageBase=0 \
    -Wl,--version-script=${ENCLAVE_DIR}/TestEnclave.lds")

add_custom_command(TARGET TestEnclave
        POST_BUILD
        COMMAND ${SGX_ENCLAVE_SIGNER} sign
        -key ${CMAKE_CURRENT_SOURCE_DIR}/TestEnclave_private.pem
        -config ${CMAKE_CURRENT_SOURCE_DIR}/TestEnclave.config.xml
        -enclave TestEnclave.so
        -out TestEnclave.signed.so
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Signing the enclave => ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/TestEnclave.signed.so")


### are those important ##
#add_dependencies(TestEnclave ${PROJECT_NAME}_t)
#add_dependencies(TestEnclave ${PROJECT_NAME}_u)

