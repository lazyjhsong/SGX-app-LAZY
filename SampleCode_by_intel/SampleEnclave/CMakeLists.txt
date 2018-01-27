cmake_minimum_required(VERSION 3.9)
project(SampleEnclave)

set(CMAKE_CXX_STANDARD 11)

#[[add_executable(SampleEnclave
    App/Edger8rSyntax/Arrays.cpp
    App/Edger8rSyntax/Functions.cpp
    App/Edger8rSyntax/Pointers.cpp
    App/Edger8rSyntax/Types.cpp
    App/TrustedLibrary/Libc.cpp
    App/TrustedLibrary/Libcxx.cpp
    App/TrustedLibrary/Thread.cpp
    App/App.cpp
    App/App.h
    App/Enclave_u.c
    App/Enclave_u.h
    Enclave/Edger8rSyntax/Arrays.cpp
    Enclave/Edger8rSyntax/Functions.cpp
    Enclave/Edger8rSyntax/Pointers.cpp
    Enclave/Edger8rSyntax/Types.cpp
    Enclave/TrustedLibrary/Libc.cpp
    Enclave/TrustedLibrary/Libcxx.cpp
    Enclave/TrustedLibrary/Thread.cpp
    Enclave/Enclave.cpp
    Enclave/Enclave.h
    Enclave/Enclave_t.c
    Enclave/Enclave_t.h
    Include/user_types.h
    Makefile)]]

add_custom_target(app
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_target(app_clean
        COMMAND make clean
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})