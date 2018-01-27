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

/* sgx h */
#include "Enclave_t.h"

/* ecall func */
void ecall_print(const char*);
void ecall_print_trace(const char*);
int ecall_lazy_syscall(const int*);

/* user enclave func */
void enclave_printf(const char *fmt, ...);
void enclave_printf_trace(const char *fmt, ...);

#endif //SIMPLE_ENCLAVE_H
