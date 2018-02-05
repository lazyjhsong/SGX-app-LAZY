//
// Created by jhsong on 18. 1. 26.
//

#ifndef SIMPLE_HELLOWORLD_H
#define SIMPLE_HELLOWORLD_H

/* lib h */
#include <x86intrin.h>

/* sgx h */
#include "sgx_eid.h"     /* sgx_enclave_id_t */
#include "Enclave_u.h"

/* user func */
uint64_t helloworld(sgx_enclave_id_t);

#endif //SIMPLE_HELLOWORLD_H
