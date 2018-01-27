cmake_minimum_required(VERSION 3.9)
project(LocalAttestation)

set(CMAKE_CXX_STANDARD 11)

#[[add_executable(LocalAttestation
        App/App.cpp
        Enclave1/Enclave1.config.xml
        Enclave1/Enclave1.cpp
        Enclave1/Enclave1.edl
        Enclave1/Enclave1.lds
        Enclave1/Enclave1_private.pem
        Enclave1/Enclave1_t.c
        Enclave1/Enclave1_t.h
        Enclave1/Enclave1_u.c
        Enclave1/Enclave1_u.h
        Enclave1/Utility_E1.cpp
        Enclave1/Utility_E1.h
        Enclave2/Enclave2.config.xml
        Enclave2/Enclave2.cpp
        Enclave2/Enclave2.edl
        Enclave2/Enclave2.lds
        Enclave2/Enclave2_private.pem
        Enclave2/Enclave2_t.c
        Enclave2/Enclave2_t.h
        Enclave2/Enclave2_u.c
        Enclave2/Enclave2_u.h
        Enclave2/Utility_E2.cpp
        Enclave2/Utility_E2.h
        Enclave3/Enclave3.config.xml
        Enclave3/Enclave3.cpp
        Enclave3/Enclave3.edl
        Enclave3/Enclave3.lds
        Enclave3/Enclave3_private.pem
        Enclave3/Enclave3_t.c
        Enclave3/Enclave3_t.h
        Enclave3/Enclave3_u.c
        Enclave3/Enclave3_u.h
        Enclave3/Utility_E3.cpp
        Enclave3/Utility_E3.h
        Include/dh_session_protocol.h
        LocalAttestationCode/datatypes.h
        LocalAttestationCode/EnclaveMessageExchange.cpp
        LocalAttestationCode/EnclaveMessageExchange.h
        LocalAttestationCode/error_codes.h
        LocalAttestationCode/LocalAttestationCode.edl
        LocalAttestationCode/LocalAttestationCode_t.c
        LocalAttestationCode/LocalAttestationCode_t.h
        Untrusted_LocalAttestation/UntrustedEnclaveMessageExchange.cpp
        Untrusted_LocalAttestation/UntrustedEnclaveMessageExchange.h
        Makefile
        README.txt)]]

add_custom_target(app
        COMMAND make
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})