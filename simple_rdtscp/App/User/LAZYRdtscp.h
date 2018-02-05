/*
 * LAZYRdtscp.h
 * Created by jhsong on Feb 5, 2018
 */

#ifndef APP_USER_LAZYRDTSCP_H_
#define APP_USER_LAZYRDTSCP_H_

/* lib h */
#include <x86intrin.h>
#include <stdio.h>

/* sgx h */
#include "sgx_eid.h"     /* sgx_enclave_id_t */
#include "Enclave_u.h"

/* user func */
uint64_t rdtscp_test1(sgx_enclave_id_t, int);

#endif /* APP_USER_LAZYRDTSCP_H_ */
