#ifndef ENCLAVE_U_H__
#define ENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_satus_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print, (const char* str));
void SGX_UBRIDGE(SGX_NOCONVENTION, ocall_print_trace, (const char* str));
int SGX_UBRIDGE(SGX_NOCONVENTION, ocall_lazy_syscall, (const int* no));

sgx_status_t ecall_print(sgx_enclave_id_t eid, const char* str);
sgx_status_t ecall_print_trace(sgx_enclave_id_t eid, const char* str);
sgx_status_t ecall_lazy_syscall(sgx_enclave_id_t eid, int* retval, const int* no);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
