/*
 * LAZYRdtscp.h
 * Created by jhsong on Feb 5, 2018
 */

#ifndef APP_USER_LAZYRDTSCP_H_
#define APP_USER_LAZYRDTSCP_H_

/* lib h */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <x86intrin.h>
#include <cpuid.h>
#include <sched.h>
#include <unistd.h>

/* sgx h */
#include "sgx_eid.h"     /* sgx_enclave_id_t */
#include "Enclave_u.h"

/* user h */
#include "envdefine.h"

/* extern u var */
extern int* App_int_var;
extern int* App_int_dummy;
extern int* App_int_tmp;
extern char* App_char_var;
extern char* App_char_tmp;
extern char* App_char_ptr;

/* user func */
void test_setup_var(sgx_enclave_id_t, size_t, int, int);
void test_reset_int_tmp(sgx_enclave_id_t);
void test_reset_char_tmp(sgx_enclave_id_t, size_t);
void test_free_var(sgx_enclave_id_t);

uint64_t test_ecall_in_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_out_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_inout_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_in_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_out_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_inout_rdtscp(sgx_enclave_id_t);

uint64_t test_ecall_in_pass_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_out_pass_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_inout_pass_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_in_pass_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_out_pass_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_inout_pass_rdtscp(sgx_enclave_id_t);

uint64_t test_ecall_in_set_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_out_set_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_inout_set_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_in_set_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_out_set_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_inout_set_rdtscp(sgx_enclave_id_t);

uint64_t test_ecall_in_cp_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_out_cp_rdtscp(sgx_enclave_id_t);
uint64_t test_ecall_inout_cp_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_in_cp_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_out_cp_rdtscp(sgx_enclave_id_t);
uint64_t test_ocall_inout_cp_rdtscp(sgx_enclave_id_t);

#endif /* APP_USER_LAZYRDTSCP_H_ */
