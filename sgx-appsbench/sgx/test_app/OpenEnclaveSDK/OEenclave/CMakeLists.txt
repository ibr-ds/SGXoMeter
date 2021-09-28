# Compile EDL file and generate required files for wrapper function
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave_t.c OETestEnclave_t.h OETestEnclave_args.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.edl
    COMMAND 
        openenclave::oeedger8r --trusted ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.edl
        --search-path ${OE_INCLUDEDIR} 
        --search-path ${OE_INCLUDEDIR}/openenclave/edl/sgx
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        COMMENT "Creating OETestApp_t.c")

set(OE_ENCL_TEST_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/OEtests)

file(GLOB OETrusted_Cpp_Files
	    "${OE_ENCL_TEST_DIR}/*.cpp"
        "${COMMON_TEST_SOURCES}/*.cpp"
        "${LIBSODIUM_DIR}/*.cpp")

file(GLOB OETrusted_C_Files
	    "${OE_ENCL_TEST_DIR}/*.c"
        "${COMMON_TEST_SOURCES}/*.c"
        "${LIBSODIUM_DIR}/*.c")

set(TRUSTED_TEST_SRCS            ${OETrusted_Cpp_Files} ${OETrusted_C_Files})

add_executable(OEenclave OETestEnclave.cpp ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave_t.c ${TRUSTED_TEST_SRCS})  

target_compile_definitions(OEenclave PUBLIC OE_ENCLAVE_CONTEXT)

target_compile_definitions(OEenclave PUBLIC OE_API_VERSION=2) # use latest OE API version

# Need for the generated file testapp_t.h
target_include_directories(OEenclave PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${Global_Variables_Path} ${COMMON_TEST_HEADERS} ${COMMON_HEADERS_PATH} ${ENCL_TEST_DIR} ${LIBSODIUM_DIR}/include ${LIBSODIUM_DIR}/include/sodium ${GCC_PATH})


target_link_libraries(OEenclave openenclave::oeenclave-lvi-cfg openenclave::oecrypto${OE_CRYPTO_LIB}-lvi-cfg openenclave::oelibcxx-lvi-cfg openenclave::oecryptoopenssl-lvi-cfg) #"-L${OPENSSL_LIBRARY_PATH} -Wl,--whole-archive -l${OpenSSL_CRYP_LIBRARY}") # use oelibc if no C++ is used

# Sign enclave
add_custom_command(
    OUTPUT OEenclave.signed
    DEPENDS OEenclave OETestEnclave.conf 
    COMMAND openenclave::oesign sign -e $<TARGET_FILE:OEenclave> -c
        ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.conf -k ${OEENCL_DIR}/TestEnclave_private.pem
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "OE-Enclave signed")

add_custom_target(sign ALL DEPENDS OEenclave.signed)