########################## Build the GrapheneBench Part ##########################
set(BASELINE_DIR		                "${CMAKE_CURRENT_SOURCE_DIR}")
set(BASELINE_INCLUDE_PATHS 		         ${BASELINE_DIR} ${Global_Variables_Path} ${Utils_Path} ${BASELINE_OPENSSL_LIBRARY_INC} ${COMMON_HEADERS_PATH})
set(GRAPHENE_APP_NAME                           GrapheneBench)

set(CMAKE_C_FLAGS 		                "${CMAKE_C_FLAGS} -O2 -fPIC -fpie -fstack-protector -Wformat -Wformat-security -Wno-attributes")
set(CMAKE_CXX_FLAGS 		            "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11")


file(GLOB Tests_C_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c"
        "${LIBSODIUM_DIR}/*.c"
        "../commonTestFiles/seeq/*.c")    

file(GLOB Test_Cpp_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
        "${LIBSODIUM_DIR}/*.cpp")

set(BASELINE_INCLUDE_PATHS              ${BASELINE_INCLUDE_PATHS} ${SGXSDK_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/tests/ ../commonTestFiles/seeq/ ${LIBSODIUM_DIR}/include ${LIBSODIUM_DIR}/include/sodium ${GCC_PATH})


set(BASELINE_Link_Flags		            "${Security_Link_Flags} -L${BASELINE_OPENSSL_LIBRARY_PATH} -lcrypto -lpthread -L${SGX_LIBRARY_PATH} -lsgx_tcrypto -l${SGX_TSVC_LIB}")
set(BASELINE_SRC_FILES 		             ../Utils/InputParser.c BaseApp.cpp  BenchThread.cpp ${Tests_C_FILES} ${Test_Cpp_FILES})


add_executable(${GRAPHENE_APP_NAME}          ${BASELINE_SRC_FILES})

target_compile_definitions(${GRAPHENE_APP_NAME} PUBLIC BASELINE_CONTEXT)

set_target_properties(${GRAPHENE_APP_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_include_directories(${GRAPHENE_APP_NAME} PRIVATE
        ${BASELINE_INCLUDE_PATHS}
        )

target_link_libraries(${GRAPHENE_APP_NAME}   ${BASELINE_Link_Flags} ${ARGON2_LIBRARY_PATH}/${ARGON2_LIBRARY_NAME})



