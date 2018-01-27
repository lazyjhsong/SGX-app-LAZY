//
// Created by jhsong on 18. 1. 26.
//

#include "HelloWorld.h"

void helloworld(sgx_enclave_id_t id)
{
    const char str[] = "\nHelloWorld!";
    ecall_print_trace(id, str);
}