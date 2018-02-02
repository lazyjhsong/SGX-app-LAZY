//
// Created by jhsong on 18. 1. 27.
//

#ifndef SIMPLE_LAZYSYSCALL_H
#define SIMPLE_LAZYSYSCALL_H

/* lib h */

/* sgx h */
#include "Enclave_u.h"

/* LAZY System Call Number */
#define __NR_lazycall	548

/* user func */
int lazy_syscall(sgx_enclave_id_t);

#endif //SIMPLE_LAZYSYSCALL_H
