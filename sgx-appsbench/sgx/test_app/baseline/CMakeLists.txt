########################## Build the Baseline Part of BenchApp ##########################
set(BASELINE_DIR		                "${CMAKE_CURRENT_SOURCE_DIR}")
set(BASELINE_INCLUDE_PATHS 		         ${BASELINE_DIR} ${Global_Variables_Path} ${Utils_Path} ${BASELINE_OPENSSL_LIBRARY_INC})

set(CMAKE_C_FLAGS 		                "${CMAKE_C_FLAGS} -fPIC -fpie -fstack-protector -Wformat -Wformat-security -Wno-attributes")
set(CMAKE_CXX_FLAGS 		            "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} -std=c++11")

file(GLOB Tests_C_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/seeq/*.c")      #ToDo move these two to the outside and adjust them accordingly in the cmakelist file used in


#list(REMOVE_ITEM Tests_C_FILES "tests/missing_funcs.c")

set(BASELINE_Link_Flags		            "${Security_Link_Flags} -L${BASELINE_OPENSSL_LIBRARY_PATH} -lcrypto -lpthread")
set(BASELINE_SRC_FILES 		             ../Utils/InputParser.c BaseApp.cpp  BenchThread.cpp ${Tests_C_FILES})

set(BASE_APP_NAME                        BaselineApp)

add_executable(${BASE_APP_NAME}          ${BASELINE_SRC_FILES})

set_target_properties(${BASE_APP_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}
        )

target_include_directories(${BASE_APP_NAME} PRIVATE
        ${BASELINE_INCLUDE_PATHS}
        )

target_link_libraries(${BASE_APP_NAME}   ${BASELINE_Link_Flags})