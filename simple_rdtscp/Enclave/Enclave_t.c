#include "Enclave_t.h"

#include "sgx_trts.h" /* for sgx_ocalloc, sgx_is_outside_enclave */

#include <errno.h>
#include <string.h> /* for memcpy etc */
#include <stdlib.h> /* for malloc/free etc */

#define CHECK_REF_POINTER(ptr, siz) do {	\
	if (!(ptr) || ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)

#define CHECK_UNIQUE_POINTER(ptr, siz) do {	\
	if ((ptr) && ! sgx_is_outside_enclave((ptr), (siz)))	\
		return SGX_ERROR_INVALID_PARAMETER;\
} while (0)


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

static sgx_status_t SGX_CDECL sgx_ecall_print(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_print_t));
	ms_ecall_print_t* ms = SGX_CAST(ms_ecall_print_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_str = ms->ms_str;
	size_t _len_str = _tmp_str ? strlen(_tmp_str) + 1 : 0;
	char* _in_str = NULL;

	CHECK_UNIQUE_POINTER(_tmp_str, _len_str);

	if (_tmp_str != NULL && _len_str != 0) {
		_in_str = (char*)malloc(_len_str);
		if (_in_str == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_str, _tmp_str, _len_str);
		_in_str[_len_str - 1] = '\0';
	}
	ecall_print((const char*)_in_str);
err:
	if (_in_str) free((void*)_in_str);

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_print_trace(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_print_trace_t));
	ms_ecall_print_trace_t* ms = SGX_CAST(ms_ecall_print_trace_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	char* _tmp_str = ms->ms_str;
	size_t _len_str = _tmp_str ? strlen(_tmp_str) + 1 : 0;
	char* _in_str = NULL;

	CHECK_UNIQUE_POINTER(_tmp_str, _len_str);

	if (_tmp_str != NULL && _len_str != 0) {
		_in_str = (char*)malloc(_len_str);
		if (_in_str == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_str, _tmp_str, _len_str);
		_in_str[_len_str - 1] = '\0';
	}
	ecall_print_trace((const char*)_in_str);
err:
	if (_in_str) free((void*)_in_str);

	return status;
}

static sgx_status_t SGX_CDECL sgx_ecall_lazy_syscall(void* pms)
{
	CHECK_REF_POINTER(pms, sizeof(ms_ecall_lazy_syscall_t));
	ms_ecall_lazy_syscall_t* ms = SGX_CAST(ms_ecall_lazy_syscall_t*, pms);
	sgx_status_t status = SGX_SUCCESS;
	int* _tmp_no = ms->ms_no;
	size_t _len_no = sizeof(*_tmp_no);
	int* _in_no = NULL;

	CHECK_UNIQUE_POINTER(_tmp_no, _len_no);

	if (_tmp_no != NULL && _len_no != 0) {
		_in_no = (int*)malloc(_len_no);
		if (_in_no == NULL) {
			status = SGX_ERROR_OUT_OF_MEMORY;
			goto err;
		}

		memcpy((void*)_in_no, _tmp_no, _len_no);
	}
	ms->ms_retval = ecall_lazy_syscall((const int*)_in_no);
err:
	if (_in_no) free((void*)_in_no);

	return status;
}

SGX_EXTERNC const struct {
	size_t nr_ecall;
	struct {void* ecall_addr; uint8_t is_priv;} ecall_table[3];
} g_ecall_table = {
	3,
	{
		{(void*)(uintptr_t)sgx_ecall_print, 0},
		{(void*)(uintptr_t)sgx_ecall_print_trace, 0},
		{(void*)(uintptr_t)sgx_ecall_lazy_syscall, 0},
	}
};

SGX_EXTERNC const struct {
	size_t nr_ocall;
	uint8_t entry_table[3][3];
} g_dyn_entry_table = {
	3,
	{
		{0, 0, 0, },
		{0, 0, 0, },
		{0, 0, 0, },
	}
};


sgx_status_t SGX_CDECL ocall_print(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_t);
	void *__tmp = NULL;

	ocalloc_size += (str != NULL && sgx_is_within_enclave(str, _len_str)) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_t));

	if (str != NULL && sgx_is_within_enclave(str, _len_str)) {
		ms->ms_str = (char*)__tmp;
		__tmp = (void *)((size_t)__tmp + _len_str);
		memcpy((void*)ms->ms_str, str, _len_str);
	} else if (str == NULL) {
		ms->ms_str = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(0, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_print_trace(const char* str)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_str = str ? strlen(str) + 1 : 0;

	ms_ocall_print_trace_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_print_trace_t);
	void *__tmp = NULL;

	ocalloc_size += (str != NULL && sgx_is_within_enclave(str, _len_str)) ? _len_str : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_print_trace_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_print_trace_t));

	if (str != NULL && sgx_is_within_enclave(str, _len_str)) {
		ms->ms_str = (char*)__tmp;
		__tmp = (void *)((size_t)__tmp + _len_str);
		memcpy((void*)ms->ms_str, str, _len_str);
	} else if (str == NULL) {
		ms->ms_str = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(1, ms);


	sgx_ocfree();
	return status;
}

sgx_status_t SGX_CDECL ocall_lazy_syscall(int* retval, const int* no)
{
	sgx_status_t status = SGX_SUCCESS;
	size_t _len_no = sizeof(*no);

	ms_ocall_lazy_syscall_t* ms = NULL;
	size_t ocalloc_size = sizeof(ms_ocall_lazy_syscall_t);
	void *__tmp = NULL;

	ocalloc_size += (no != NULL && sgx_is_within_enclave(no, _len_no)) ? _len_no : 0;

	__tmp = sgx_ocalloc(ocalloc_size);
	if (__tmp == NULL) {
		sgx_ocfree();
		return SGX_ERROR_UNEXPECTED;
	}
	ms = (ms_ocall_lazy_syscall_t*)__tmp;
	__tmp = (void *)((size_t)__tmp + sizeof(ms_ocall_lazy_syscall_t));

	if (no != NULL && sgx_is_within_enclave(no, _len_no)) {
		ms->ms_no = (int*)__tmp;
		__tmp = (void *)((size_t)__tmp + _len_no);
		memcpy((void*)ms->ms_no, no, _len_no);
	} else if (no == NULL) {
		ms->ms_no = NULL;
	} else {
		sgx_ocfree();
		return SGX_ERROR_INVALID_PARAMETER;
	}
	
	status = sgx_ocall(2, ms);

	if (retval) *retval = ms->ms_retval;

	sgx_ocfree();
	return status;
}

