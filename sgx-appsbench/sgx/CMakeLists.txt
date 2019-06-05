cmake_minimum_required(VERSION 3.4)
project(SGX-AppsBench "C" "CXX")


##########################  Build Environment Variables ##########################
set(ROOT_DIR 				${CMAKE_CURRENT_SOURCE_DIR})
set(PACKAGE_LIB 			${ROOT_DIR}/../package/lib64/)
set(PACKAGE_INC 			${ROOT_DIR}/../package/include/)
set(TRUSTED_LIB_DIR 			${ROOT_DIR}/libsgx_tsgxssl/)
set(UNTRUSTED_LIB_DIR 			${ROOT_DIR}/libsgx_usgxssl/)
set(TEST_DIR 				${ROOT_DIR}/test_app/)
set(OS_ID				0)
set(LINUX_SGX_BUILD 			0)
set(TRUSTED_LIB 			libsgx_tsgxssl.a)
set(UNTRUSTED_LIB 			libsgx_usgxssl.a)
set(VCC 				@${CMAKE_C_COMPILER})
set(VCXX 				@${CMAKE_CXX_COMPILER})
set(OBJDIR 				release)

if(NOT DESTDIR)
    	set(DESTDIR 			/opt/intel/sgxssl/)
endif()

if(NOT DEBUG)
	set(DEBUG 			0 CACHE STRING "Set the debug value 1(on) or 0(off)")
endif()

execute_process (
    	COMMAND mkdir -p ${PACKAGE_LIB}
)

set(UBUNTU_CONFNAME			/usr/include/x86_64-linux-gnu/bits/confname.h)
if(EXISTS "${UBUNTU_CONFNAME}")
   	set(OS_ID			1)
else()
   	set(OS_ID			2)
endif()

if(${DEBUG} EQUAL 1)
	set(OBJDIR 			debug)	
	set(OPENSSL_LIB 		libsgx_tsgxssl_cryptod.a)
	set(TRUSTED_LIB 		ibsgx_tsgxssld.a)
	set(UNTRUSTED_LIB 		libsgx_usgxssld.a)
else()
	set(OBJDIR 			release)	
	set(OPENSSL_LIB 		libsgx_tsgxssl_cryptod.a)
	set(TRUSTED_LIB 		ibsgx_tsgxssld.a)
	set(UNTRUSTED_LIB 		libsgx_usgxssld.a)
endif()

if(${VERBOSE} EQUAL 1)
	set(VCC				${CMAKE_C_COMPILER})
	set(VCXX			${CMAKE_CXX_COMPILER})
else()
	set(VCC 			@${CMAKE_C_COMPILER})
	set(VCXX 			@${CMAKE_CXX_COMPILER})
endif()


########################## SGX SETTINGS ##########################
set(SGX_SDK 				/opt/intel/sgxsdk  CACHE PATH "Set the path to the SGX-SDK directory")
set(SGX_ARCH 				x64)
set(SGX_MODE 				HW CACHE STRING "SGX mode: SIM or HW") # SGX mode: sim, hw
set(SGX_BUILD				DEBUG CACHE STRING "Build: DEBUG, PRERELEASE or RELEASE")
include (cmake/Init.cmake)
include (cmake/ConfigSGX.cmake)

########################## Build the benchmarking tool  ##########################

add_subdirectory(test_app)


