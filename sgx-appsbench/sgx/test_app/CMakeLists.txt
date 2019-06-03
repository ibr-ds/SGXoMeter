project(SGX-AppsBench)
cmake_minimum_required(VERSION 3.4)

# buildAll calls make all to build everything

add_custom_target(buildAll
        COMMAND make all
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        )

# cleanAll calls make clean

add_custom_target(cleanALL
        COMMAND make clean
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        )
