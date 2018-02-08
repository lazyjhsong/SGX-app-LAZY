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
#include "User/HelloWorld.h"
#include "User/LazySyscall.h"
#include "User/LAZYRdtscp.h"
#include "envdefine.h"

/* ocall func */
void ocall_print(const char*);
void ocall_print_trace(const char*);
int ocall_lazy_syscall(const int*);

void ocall_in_rdtscp(int*);
void ocall_out_rdtscp(int*);
void ocall_inout_rdtscp(int*);

void ocall_in_pass_rdtscp(char*, size_t);
void ocall_out_pass_rdtscp(char*, size_t);
void ocall_inout_pass_rdtscp(char*, size_t);

void ocall_in_set_rdtscp(char*, size_t);
void ocall_out_set_rdtscp(char*, size_t);
void ocall_inout_set_rdtscp(char*, size_t);

void ocall_in_cp_rdtscp(char*, size_t);
void ocall_out_cp_rdtscp(char*, size_t);
void ocall_inout_cp_rdtscp(char*, size_t);

/* user func */
//void app_print_error_msg(sgx_status_t);
int app_init_enclave(void);
int app_destroy_enclave(sgx_enclave_id_t);
void app_setup_var(sgx_enclave_id_t, size_t, int, int);
void app_reset_int_tmp(sgx_enclave_id_t);
void app_reset_char_tmp(sgx_enclave_id_t, size_t);
void app_free_var(sgx_enclave_id_t);

#endif //SIMPLE_APP_H
