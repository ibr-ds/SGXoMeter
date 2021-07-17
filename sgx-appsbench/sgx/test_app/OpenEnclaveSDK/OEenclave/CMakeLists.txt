
# Compile EDL file and generate required files for wrapper function
add_custom_command(
    OUTPUT OETestEnclave_t.h OETestEnclave_t.c OETestEnclave_args.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.edl
    COMMAND 
        openenclave::oeedger8r --trusted ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.edl
        --search-path ${OE_INCLUDEDIR} 
        --search-path ${OE_INCLUDEDIR}/openenclave/edl/sgx
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} # unklar, funktioniert so aber 
        COMMENT "Creating OETestApp_t.c")

set(OE_ENCL_TEST_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/OEtests)

file(GLOB OETrusted_Cpp_Files
	    "${OE_ENCL_TEST_DIR}/*.cpp")

file(GLOB OETrusted_C_Files
	    "${OE_ENCL_TEST_DIR}/*.c"
	    "../../commonTestFiles/seeq/*.c")

set(TRUSTED_TEST_SRCS           ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave_t.c ${OETrusted_Cpp_Files} ${OETrusted_C_Files})

#add_library(OE_TEST_LIB SHARED ${TRUSTED_TEST_SRCS})


add_executable(OEenclave OETestEnclave.cpp ${TRUSTED_TEST_SRCS})  
#${ENCL_TEST_DIR}/marceltest.c

target_compile_definitions(OEenclave PUBLIC OE_API_VERSION=2) # use latest OE API version

# Need for the generated file testapp_t.h
target_include_directories(OEenclave PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${Global_Variables_Path} ${COMMON_TEST_HEADERS} ${COMMON_HEADERS_PATH} ${ENCL_TEST_DIR} ${PACKAGE_INC}/openssl)


target_link_libraries(OEenclave openenclave::oeenclave openenclave::oecrypto${OE_CRYPTO_LIB} openenclave::oelibcxx) # use oelibc if no C++ is used

# add_custom_command(
#   OUTPUT private.pem public.pem
#   COMMAND openssl genrsa -out private.pem -3 3072
#   COMMAND openssl rsa -in private.pem -pubout -out public.pem
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#   COMMENT "SSL Done")

# Sign enclave
add_custom_command(
    OUTPUT OEenclave.signed
    DEPENDS OEenclave OETestEnclave.conf #private.pem
    COMMAND openenclave::oesign sign -e $<TARGET_FILE:OEenclave> -c
        ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.conf -k ${OEENCL_DIR}/TestEnclave_private.pem
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "OE-Enclave signed")
    #    -out ${SIGNED_OE_ENCLAVE_NAME}
    #BYPRODUCTS ${SIGNED_OE_ENCLAVE_NAME}

add_custom_target(sign ALL DEPENDS OEenclave.signed)