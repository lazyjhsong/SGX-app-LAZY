#include "Enclave_u.h"
#include <errno.h>

typedef struct ms_ecall_print_t {
	char* ms_str;
} ms_ecall_print_t;

typedef struct ms_ecall_print_trace_t {
	char* ms_str;
} ms_ecall_print_trace_t;

typedef struct ms_ecall_lazy_syscall_t {
	int ms_retval;
	int* ms_no;
} ms_ecall_lazy_syscall_t;

typedef struct ms_ocall_print_t {
	char* ms_str;
} ms_ocall_print_t;

typedef struct ms_ocall_print_trace_t {
	char* ms_str;
} ms_ocall_print_trace_t;

typedef struct ms_ocall_lazy_syscall_t {
	int ms_retval;
	int* ms_no;
} ms_ocall_lazy_syscall_t;

static sgx_status_t SGX_CDECL Enclave_ocall_print(void* pms)
{
	ms_ocall_print_t* ms = SGX_CAST(ms_ocall_print_t*, pms);
	ocall_print((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_print_trace(void* pms)
{
	ms_ocall_print_trace_t* ms = SGX_CAST(ms_ocall_print_trace_t*, pms);
	ocall_print_trace((const char*)ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL Enclave_ocall_lazy_syscall(void* pms)
{
	ms_ocall_lazy_syscall_t* ms = SGX_CAST(ms_ocall_lazy_syscall_t*, pms);
	ms->ms_retval = ocall_lazy_syscall((const int*)ms->ms_no);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[3];
} ocall_table_Enclave = {
	3,
	{
		(void*)Enclave_ocall_print,
		(void*)Enclave_ocall_print_trace,
		(void*)Enclave_ocall_lazy_syscall,
	}
};
sgx_status_t ecall_print(sgx_enclave_id_t eid, const char* str)
{
	sgx_status_t status;
	ms_ecall_print_t ms;
	ms.ms_str = (char*)str;
	status = sgx_ecall(eid, 0, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_print_trace(sgx_enclave_id_t eid, const char* str)
{
	sgx_status_t status;
	ms_ecall_print_trace_t ms;
	ms.ms_str = (char*)str;
	status = sgx_ecall(eid, 1, &ocall_table_Enclave, &ms);
	return status;
}

sgx_status_t ecall_lazy_syscall(sgx_enclave_id_t eid, int* retval, const int* no)
{
	sgx_status_t status;
	ms_ecall_lazy_syscall_t ms;
	ms.ms_no = (int*)no;
	status = sgx_ecall(eid, 2, &ocall_table_Enclave, &ms);
	if (status == SGX_SUCCESS && retval) *retval = ms.ms_retval;
	return status;
}

