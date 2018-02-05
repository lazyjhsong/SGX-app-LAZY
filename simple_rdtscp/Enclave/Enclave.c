//
// Created by jhsong on 18. 1. 27.
//

/* user h */
#include "Enclave.h"

/* ecall func begin */
void ecall_print(const char* str)
{
    enclave_printf("%s\n", str);
}

void ecall_print_trace(const char* str)
{
    enclave_printf_trace("%s -> [ECall]", str);
}

int ecall_lazy_syscall(const int* no)
{
    int ret = 0;
    ocall_lazy_syscall(&ret, no);
    if(ret==0)
    { enclave_printf("LAZY System Call Success -> [ECall]"); }
    else
    { enclave_printf("LAZY System Call fail -> [ECall]"); }
    return ret;
}

void ecall_rdtscp_test1(int* var)
{
	// do something
	/* RDTSCP var */
	unsigned int junk = 0;
	register uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	start = __rdtscp( & junk);
	end = __rdtscp( & junk);

}
/* ecall func end */

/* user enclave func begin */
void enclave_printf(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print(buf);
}

void enclave_printf_trace(const char *fmt, ...)
{
    char buf[BUFSIZ] = {'\0'};
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, BUFSIZ, fmt, ap);
    va_end(ap);
    ocall_print_trace(buf);
}
/* user enclave func begin */


