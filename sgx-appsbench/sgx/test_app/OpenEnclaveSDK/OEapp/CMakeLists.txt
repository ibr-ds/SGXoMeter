add_custom_command(
    OUTPUT OETestEnclave_u.h OETestEnclave_u.c OETestEnclave_args.h
    DEPENDS ${OEENCL_DIR}/OETestEnclave.edl
    COMMAND 
        openenclave::oeedger8r --untrusted ${OEENCL_DIR}/OETestEnclave.edl
        --search-path ${OE_INCLUDEDIR} 
        --search-path ${OE_INCLUDEDIR}/openenclave/edl/sgx
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Creating OETestApp_u.c")


add_executable(OEBenchApp OETestApp.cpp ../../Utils/InputParser.c OETestEnclave_u.c)

set_target_properties(OEBenchApp
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)


target_include_directories(
  OEBenchApp PRIVATE # Needed for the generated file testapp_u.h
                          ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(OEBenchApp PRIVATE
${Global_Variables_Path} ${Utils_Path} ${COMMON_HEADERS_PATH})



target_link_libraries(OEBenchApp openenclave::oehost)
