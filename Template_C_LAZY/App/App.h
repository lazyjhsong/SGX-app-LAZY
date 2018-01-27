//
// Created by jhsong on 18. 1. 26.
//

#ifndef SIMPLE_APP_H
#define SIMPLE_APP_H

/* lib h */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

/* sgx h */
#include "sgx_error.h"       /* sgx_status_t */
#include "sgx_eid.h"     /* sgx_enclave_id_t */
#include "Enclave_u.h"

/* user h */
#include "Enclave/Enclave_Handler.h"

/* ocall func */
void ocall_print(const char*);
void ocall_print_trace(const char*);

/* user func */
int app_init_enclave(void);
int app_destroy_enclave(sgx_enclave_id_t);

#endif //SIMPLE_APP_H
