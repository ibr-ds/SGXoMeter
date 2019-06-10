project(SGX-AppsBench)					#delete this because it will be called from the above cmakelists
cmake_minimum_required(VERSION 3.4)			#delete this because it will be callled from the above cmakelists



########################## Usefull Cmake Macros ##########################
macro(check_add_definition VARNAME VALUE)
    if(${VARNAME})
        add_definitions(-D${VALUE})        # Checks if the VARNAME IS ON and then add the VALUE as compiler variable
    endif()
endmacro()




########################## Inlcude the Globale and Test Variables ##########################
include (cmake/GlobalVariables.cmake)
include (cmake/TestVariables.cmake)


########################## Build The Untrusted Part ##########################
add_subdirectory(app)

########################## Build the Trusted Part ##########################
add_subdirectory(enclave)


########################## This is only for gui tests (delete it when finished)##########################
#set(INPUT_DNA_VALUE				"ACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCTCGT\n
#ACCTCGTAAAAGCTATAGACTTGCATGTTACAAATAAAGCAATAGCATCA\n
#           	       CATGTTACAAATAAAGCAATAGCATCA\n
#CATGTTACAAA                       TAAAGCAATAGCATCA\n
#                      CATOGTTACAAATAAAGCAATAGCATCA\n
#ACCTCGTAAAAGCTATAGACTTG" CACHE STRING "The required DNA sequence for the search/matching")
#set(DEBUG haha)
#set(DEBAG hoho)
#if(DEBUG STREQUAL "haha" AND DEBAG STREQUAL "hoho")
#	message(STATUS "${DEBUG} is the value of DEBUG variable")
#	message(${CMAKE_SOURCE_DIR})
#endif()
#message(${INPUT_DNA_VALUE})
#set(CHECK NO CACHE BOOL "set the boolean for the test")
#set(INTEG 100 CACHE STRING "enter a number here")

#if(INTEG GREATER 100)
#	add_definitions(-DINTEG)
#	execute_process (
#       	COMMAND echo "building the INTEG with value : ${INTEG}"
#  	)
#	message("haleloia")
#endif()

#check_add_definition(CHECK "haha")
#if(CHECK)
#    set(TEST ../blabla CACHE STRING "test value:")
#    execute_process (
#        COMMAND echo "building the test with value : ${TEST}"
#    )
#    execute_process (
#        COMMAND echo "current directory is : ${CMAKE_CURRENT_SOURCE_DIR} and c compiler is ${CMAKE_C_COMPILER} and cxx is ${CMAKE_CXX_COMPILER} "
#    )
#    execute_process (
#        COMMAND mkdir -p ${TEST}
#    )
#endif()



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
