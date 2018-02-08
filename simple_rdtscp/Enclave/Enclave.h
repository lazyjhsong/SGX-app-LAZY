//
// Created by jhsong on 18. 1. 27.
//

#ifndef SIMPLE_ENCLAVE_H
#define SIMPLE_ENCLAVE_H

/* lib h */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/* sgx h */
#include "Enclave_t.h"
#include "sys/_types.h"
#include "sgx_cpuid.h"
#include "envdefine.h"

/* ecall func */
void ecall_print(const char*);
void ecall_print_trace(const char*);
int ecall_lazy_syscall(const int*);

void ecall_in_rdtscp(int*);
void ecall_out_rdtscp(int*);
void ecall_inout_rdtscp(int*);
void ecall_ocall_in_rdtscp(int*);
void ecall_ocall_out_rdtscp(int*);
void ecall_ocall_inout_rdtscp(int*);
void ecall_ocall_in_rdtscp_dummy(int*);
void ecall_ocall_out_rdtscp_dummy(int*);
void ecall_ocall_inout_rdtscp_dummy(int*);

void ecall_in_pass_rdtscp(char*, size_t);
void ecall_out_pass_rdtscp(char*, size_t);
void ecall_inout_pass_rdtscp(char*, size_t);
void ecall_ocall_in_pass_rdtscp(int*);
void ecall_ocall_out_pass_rdtscp(int*);
void ecall_ocall_inout_pass_rdtscp(int*);
void ecall_ocall_in_pass_rdtscp_dummy(int*);
void ecall_ocall_out_pass_rdtscp_dummy(int*);
void ecall_ocall_inout_pass_rdtscp_dummy(int*);

void ecall_in_set_rdtscp(char*, size_t);
void ecall_out_set_rdtscp(char*, size_t);
void ecall_inout_set_rdtscp(char*, size_t);
void ecall_ocall_in_set_rdtscp(int*);
void ecall_ocall_out_set_rdtscp(int*);
void ecall_ocall_inout_set_rdtscp(int*);
void ecall_ocall_in_set_rdtscp_dummy(int*);
void ecall_ocall_out_set_rdtscp_dummy(int*);
void ecall_ocall_inout_set_rdtscp_dummy(int*);

void ecall_in_cp_rdtscp(char*, size_t);
void ecall_out_cp_rdtscp(char*, size_t);
void ecall_inout_cp_rdtscp(char*, size_t);
void ecall_ocall_in_cp_rdtscp(int*);
void ecall_ocall_out_cp_rdtscp(int*);
void ecall_ocall_inout_cp_rdtscp(int*);
void ecall_ocall_in_cp_rdtscp_dummy(int*);
void ecall_ocall_out_cp_rdtscp_dummy(int*);
void ecall_ocall_inout_cp_rdtscp_dummy(int*);

void ecall_setup_var(size_t*);
void ecall_reset_int_tmp(void);
void ecall_reset_char_tmp(size_t*);
void ecall_free_var(void);

/* user enclave func */
void enclave_printf(const char*, ...);
void enclave_printf_trace(const char*, ...);

#endif //SIMPLE_ENCLAVE_H
