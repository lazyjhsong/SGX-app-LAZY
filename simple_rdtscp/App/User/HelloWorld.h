//
// Created by jhsong on 18. 1. 26.
//

#ifndef SIMPLE_HELLOWORLD_H
#define SIMPLE_HELLOWORLD_H

/* sgx h */
#include "sgx_eid.h"     /* sgx_enclave_id_t */
#include "Enclave_u.h"

void helloworld(sgx_enclave_id_t);

#endif //SIMPLE_HELLOWORLD_H
