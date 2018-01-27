cmake_minimum_required(VERSION 3.9)
project(SampleCode_template)

set(CMAKE_CXX_STANDARD 11)

#[[add_executable(SampleCode_template
        App/sgx_utils/sgx_utils.cpp
        App/sgx_utils/sgx_utils.h
        App/App.cpp
        App/Enclave_u.c
        App/Enclave_u.h
        Enclave/Sealing/Sealing.cpp
        Enclave/Enclave.cpp
        Enclave/Enclave_t.c
        Enclave/Enclave_t.h
        Makefile)]]

add_custom_target(app
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_target(app_realease
        COMMAND make SGX_DEBUG=0
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})