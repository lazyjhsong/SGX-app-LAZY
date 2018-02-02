#ifndef ENCLAVE_T_H__
#define ENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif


void ecall_print(const char* str);
void ecall_print_trace(const char* str);
int ecall_lazy_syscall(const int* no);

sgx_status_t SGX_CDECL ocall_print(const char* str);
sgx_status_t SGX_CDECL ocall_print_trace(const char* str);
sgx_status_t SGX_CDECL ocall_lazy_syscall(int* retval, const int* no);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
