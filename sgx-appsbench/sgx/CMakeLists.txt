cmake_minimum_required(VERSION 3.11) # changed for Open Enclave Support
project(SGX-AppsBench "C" "CXX")

########################## SGX SETTINGS ##########################
set(SGX_SDK 						/opt/intel/sgxsdk  CACHE PATH "Set the path to the SGX-SDK directory")
set(SGX_SDK_VERSION					2.12 CACHE STRING "Set the wanted SGX SDK version")
set(SGX_ARCH 						x64)
set(SGX_MODE 						HW CACHE STRING "SGX mode: SIM or HW") # SGX mode: sim, hw
set(SGX_BUILD						DEBUG CACHE STRING "Build: DEBUG, PRERELEASE or RELEASE")
include(cmake/Init.cmake)
include(cmake/ConfigSGX.cmake)
include(cmake/GitUtils.cmake)



########################## Set Open Enclave SDK Variables ##########################
set(OE_ENABLE					YES CACHE BOOL "Enable Open Enclave SDK for corresponding modules.")
set(OE_CRYPTO_LIB				mbedtls CACHE STRING "Crypto library used by OE-enclaves.")
set(OE_MIRROR_ENCLAVE			YES CACHE BOOL "Enable Enclave Configuration Mirroring between SGX SDK and Open Enclave")

########################## Set Enclave Settings ############################

set(ENCL_PROD_ID				0 CACHE STRING "Set ProductID of enclave.")
set(ENCL_ISVSVN					0 CACHE STRING "Set ISVSVN of enclave.")
set(ENCL_STACK_MAXSIZE			0x90000 CACHE STRING "Set the desired maximum stack size in bytes (Hexadecimal).")
set(ENCL_HEAP_MAXSIZE			0x2000000 CACHE STRING "Set the desired maximum heap size in bytes (Hexadecimal).")
set(ENCL_TCS_NUM				10 CACHE STRING "Set the number of trusted threads.")
set(ENCL_TCS_POLICY				1 CACHE STRING "0 = bind TCS to untrusted thread || 1 = unbind them.")
set(ENCL_DISABLE_DEBUG			0 CACHE STRING "0 = DEBUG || 1 = NO DEBUG.")
set(ENCL_CONF_FILE				${CMAKE_CURRENT_SOURCE_DIR}/test_app/SGX-SDK/enclave/TestEnclave.config.xml)
set(ENCL_CONF_IN_FILE			${CMAKE_CURRENT_SOURCE_DIR}/test_app/SGX-SDK/enclave/TestEnclaveIN.config.xml)
configure_file(${ENCL_CONF_IN_FILE} ${ENCL_CONF_FILE})

########################## Set Open Enclave Enclave Settings ############################
if(OE_ENABLE)
	set(ENCL_OE_PROD_ID				0 CACHE STRING "Set ProductID of OEenclave.")
	set(ENCL_OE_ISVSVN				0 CACHE STRING "Set Security version of OEenclave.")
	set(ENCL_OE_STACK_PAGES			144 CACHE STRING "Set the desired number of stack pages for OEenclave.")
	set(ENCL_OE_HEAP_PAGES			8192 CACHE STRING "Set the desired number of heap pages for OEenclave.")
	set(ENCL_OE_TCS_NUM				10 CACHE STRING "Set the number of trusted threads for OEenclave.")
	set(ENCL_OE_DEBUG				0 CACHE STRING "1 = DEBUG || 0 = NO DEBUG")

	if(OE_MIRROR_ENCLAVE)

		set(ENCL_OE_PROD_ID			${ENCL_PROD_ID})
		set(ENCL_OE_ISVSVN			${ENCL_ISVSVN})
		set(ENCL_OE_STACK_PAGES		144)
		set(ENCL_OE_HEAP_PAGES		8192)
		set(ENCL_OE_TCS_NUM			${ENCL_TCS_NUM})
		if(ENCL_DISABLE_DEBUG)
			set(ENCL_OE_DEBUG			0)
		else()
			set(ENCL_OE_DEBUG			1)
		endif()
	endif()

	set(ENCL_OE_CONF_FILE				${CMAKE_CURRENT_SOURCE_DIR}/test_app/OpenEnclaveSDK/OEenclave/OETestEnclave.conf)
	set(ENCL_OE_CONF_IN_FILE			${CMAKE_CURRENT_SOURCE_DIR}/test_app/OpenEnclaveSDK/OEenclave/OETestEnclaveIN.conf)
	configure_file(${ENCL_OE_CONF_IN_FILE} ${ENCL_OE_CONF_FILE})

endif()



########################## Set Environment Variables ##########################
set(ROOT_DIR 						${CMAKE_CURRENT_SOURCE_DIR})
set(PACKAGE_PATH 					${ROOT_DIR}/../package)
set(PACKAGE_LIB 					${PACKAGE_PATH}/lib64)
set(PACKAGE_INC 					${PACKAGE_PATH}/include/)
set(TRUSTED_LIB_DIR 				${ROOT_DIR}/libsgx_tsgxssl/)
set(UNTRUSTED_LIB_DIR 				${ROOT_DIR}/libsgx_usgxssl/)
set(TEST_DIR 						${ROOT_DIR}/test_app/)
set(OS_ID							0)
set(LINUX_SGX_BUILD 				0)
set(TRUSTED_LIB 					libsgx_tsgxssl.a)
set(UNTRUSTED_LIB 					libsgx_usgxssl.a)
set(VCC 							@${CMAKE_C_COMPILER})
set(VCXX 							@${CMAKE_CXX_COMPILER})
set(OBJDIR 							release)

if(NOT DESTDIR)
	set(DESTDIR 					/opt/intel/sgxssl/ CACHE PATH "Set the path to the SGX-openssl directory")
endif()

if(NOT DEBUG)
	set(DEBUG 						NO CACHE BOOL "Set the debug option for the openssl libraries. Value 1(on) or 0(off)")
endif()

if(NOT VERBOSE)
	set(VERBOSE 					NO CACHE BOOL "Set '@' before the C and CXX compiler. Value 1(on) or 0(off)")
endif()

set(UBUNTU_CONFNAME					/usr/include/x86_64-linux-gnu/bits/confname.h)
if(EXISTS "${UBUNTU_CONFNAME}")
   	set(OS_ID						1)
else()
   	set(OS_ID						2)
endif()

if(DEBUG)
	set(OBJDIR 						debug)
	set(OPENSSL_LIB 				libsgx_tsgxssl_cryptod.a)
	set(TRUSTED_LIB 				ibsgx_tsgxssld.a)
	set(UNTRUSTED_LIB 				libsgx_usgxssld.a)
else()
	set(OBJDIR 						release)
	set(OPENSSL_LIB 				libsgx_tsgxssl_cryptod.a)
	set(TRUSTED_LIB 				ibsgx_tsgxssld.a)
	set(UNTRUSTED_LIB 				libsgx_usgxssld.a)
endif()

if(VERBOS)
	set(VCC							${CMAKE_C_COMPILER})
	set(VCXX						${CMAKE_CXX_COMPILER})
else()
	set(VCC 						@${CMAKE_C_COMPILER})
	set(VCXX 						@${CMAKE_CXX_COMPILER})
endif()

if(DEBUG AND SGX_BUILD STREQUAL "PRERELEASE")
    message(FATAL_ERROR "Cannot set DEBUG and SGX_PRERELEASE at the same time!!")
endif()

########################## Set OpenSSL Variables ##########################
set(OPENSSL_LIBRARY_PATH			${PACKAGE_LIB})
set(BASELINE_OPENSSL_LIBRARY_PATH	${ROOT_DIR}/../openssl/)
set(BASELINE_OPENSSL_LIBRARY_INC	${ROOT_DIR}/../openssl/include)
set(BASELINE_CRYPTO_LIB_NAME		libcrypto.a)

set(OPENSSL_PATH	${ROOT_DIR}/../openssl)

if(NOT EXISTS "${PACKAGE_PATH}")
	message(STATUS "installing necessary SGX-SSL packages")
	set(SGXSSL_PATH		${ROOT_DIR}/../sgxssl)
	execute_process(
			COMMAND mkdir -p ${SGXSSL_PATH}
			OUTPUT_QUIET
	)

	git_clone(
        PROJECT_NAME    intel-sgx-ssl
        GIT_URL         https://github.com/intel/intel-sgx-ssl.git
        GIT_TAG         lin_2.11_1.1.1g
		DIRECTORY		${SGXSSL_PATH}
		)


	if(SGX_SDK_VERSION STREQUAL "2.12")
	set(OPENSSL_VERSION		openssl-1.1.1g)
	elseif(SGX_SDK_VERSION STREQUAL "2.7")
	set(OPENSSL_VERSION 	openssl-1.1.1b)
	endif()

	message(STATUS "downloading a  ${OPENSSL_VERSION} library for the chosen SGX-SDK ${SGX_SDK_VERSION} version")
	execute_process(
			COMMAND wget -P  ${SGXSSL_PATH}/intel-sgx-ssl/openssl_source/    https://www.openssl.org/source/${OPENSSL_VERSION}.tar.gz
			OUTPUT_QUIET
			ERROR_QUIET
	)

	message(STATUS "building and extracting the SGXSSL library package")

	execute_process(
			COMMAND make all test
			WORKING_DIRECTORY ${SGXSSL_PATH}/intel-sgx-ssl/Linux
			OUTPUT_QUIET
	)
	execute_process(
			COMMAND scp -r ${SGXSSL_PATH}/intel-sgx-ssl/Linux/package ${PACKAGE_PATH}
			OUTPUT_QUIET
	)

	if(NOT EXISTS "${TRUSTED_LIB_DIR}")
	execute_process(
	COMMAND scp -r ${SGXSSL_PATH}/intel-sgx-ssl/Linux/sgx/libsgx_tsgxssl ${ROOT_DIR}
	OUTPUT_QUIET
	)
	endif()


	if(NOT EXISTS "${UNTRUSTED_LIB_DIR}")
	execute_process(
	COMMAND scp -r ${SGXSSL_PATH}/intel-sgx-ssl/Linux/sgx/libsgx_usgxssl ${ROOT_DIR}
	OUTPUT_QUIET
	)
	endif()


	message(STATUS "cleaning up")
	execute_process(
			COMMAND rm -rf ${SGXSSL_PATH}
	)

endif()

if(NOT EXISTS "${OPENSSL_PATH}")
	message(STATUS "downloading openssl library")
	execute_process (
			COMMAND mkdir -p ${OPENSSL_PATH}
			COMMAND wget https://www.openssl.org/source/openssl-1.1.1i.tar.gz --ca-directory=/etc/ssl/certs/
			OUTPUT_QUIET
			ERROR_QUIET
	)

	message(STATUS "extracting openssl library")
	execute_process(
			COMMAND tar -zxvf openssl-1.1.1i.tar.gz -C ${OPENSSL_PATH} --strip 1
			OUTPUT_QUIET
	)

	message(STATUS "configuring and building openssl library")
	execute_process(
			COMMAND bash ${OPENSSL_PATH}/config
			WORKING_DIRECTORY ${OPENSSL_PATH}
			OUTPUT_QUIET
	)
	execute_process(
			COMMAND make
			WORKING_DIRECTORY ${OPENSSL_PATH}
			OUTPUT_QUIET
	)

	message(STATUS "removing openssl tar archiv")
	execute_process(
			COMMAND rm openssl-1.1.1i.tar.gz
	)
endif()

########################## Set Argon2 Variables ##########################
set(ARGON2_LIBRARY_PATH				${ROOT_DIR})
set(ARGON2_LIBRARY_NAME				libargon2.a)

########################## Set LibSodium Variables ##########################
#set(sodium_USE_STATIC_LIBS ON)
#include(cmake/Findsodium.cmake)
#message(WARNING "sodium library is at ${sodium_LIBRARY_RELEASE}")


########################## Build the benchmarking tool  ##########################
add_subdirectory(test_app)


