//
// Created by jhsong on 18. 1. 27.
//

#include "LazySyscall.h"

int lazy_syscall(sgx_enclave_id_t id)
{
    int no, ret = 0;
    no = __NR_lazycall;
    ecall_lazy_syscall(id, &ret, &no);
    //printf("LAZY System Call return %ld\n",ret);
    return ret;
}