project(SGX-AppsBench)
cmake_minimum_required(VERSION 3.4)


######################### This is only for gui tests #####################################
set(CHECK NO CACHE BOOL "set the boolean for the test")

if(CHECK)
    set(TEST ../blabla CACHE STRING "test value:")
    execute_process (
        COMMAND echo "building the test with value : ${TEST}"
    )
    execute_process (
        COMMAND echo "current directory is : ${CMAKE_CURRENT_SOURCE_DIR} and c compiler is ${CMAKE_C_COMPILER} and cxx is ${CMAKE_CXX_COMPILER} "
    )
    execute_process (
        COMMAND mkdir -p ${TEST}
    )
endif()



# buildAll calls make all to build everything

#add_custom_target(buildAll
#        COMMAND make all
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
#        )
#
# cleanAll calls make clean
#
#add_custom_target(cleanALL
#        COMMAND make clean
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
#        )
