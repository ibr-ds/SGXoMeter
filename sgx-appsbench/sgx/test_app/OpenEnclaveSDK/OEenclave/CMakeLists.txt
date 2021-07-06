
# Compile EDL file and generate required files for wrapper function
add_custom_command(
    OUTPUT OETestEnclave_t.h OETestEnclave_t.c OETestEnclave_args.h
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.edl
    COMMAND 
        openenclave::oeedger8r --trusted ${CMAKE_CURRENT_SOURCE_DIR}/OETestEnclave.edl
        --search-path ${OE_INCLUDEDIR} 
        --search-path ${OE_INCLUDEDIR}/openenclave/edl/sgx)


add_executable(OEenclave OETestEnclave.cpp   OETestEnclave_t.c)   

target_compile_definitions(OEenclave PUBLIC OE_API_VERSION=2) # use latest OE API version

# Need for the generated file testapp_t.h
target_include_directories(OEenclave PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(OEenclave openenclave::oeenclave openenclave::oecrypto${OE_CRYPTO_LIB} openenclave::oelibcxx ) # use oelibc if no C++ is used


  