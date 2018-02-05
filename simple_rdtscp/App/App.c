//
// Created by jhsong on 18. 1. 26.
//

/* user h */
#include "App.h"

/* ocall func begin */
void ocall_print(const char* str)
{
    printf("%s\n",str);
}

void ocall_print_trace(const char* str)
{
    printf("%s -> [OCall]\n",str);
}

int ocall_lazy_syscall(const int* no)
{
    int ret = 0;
    ret = syscall(*no);
    /* for DEBUG */
    //printf("[DEBUG]syscall no : %d\n", (*no));
    if(ret==0)
    { printf("LAZY System Call Success -> [OCall]\n"); }
    else
    { printf("LAZY System Call fail -> [OCall]\n"); }
    return ret;
}

void ocall_rdtscp_test1(int* var)
{
	// do something
}
/* ocall func end */

/* user func begin */
/*void app_print_error_msg(sgx_status_t ret)
{
    handler_print_error_msg(ret);
}*/

int app_init_enclave(void)
{
    int ret = 0;
    ret = handler_init_enclave();
    return ret;
}
int app_destroy_enclave(sgx_enclave_id_t id)
{
    int ret = 0;
    ret = handler_destroy_enclave(id);
    return ret;
}
/* user func end */

/* main begin */
int main(int argc, char *argv[])
{
    /* user var */
    int ret=0, u_loop=0;
    uint64_t cycle=0;

    /* argv */
	if(argc != 2)
	{
		printf("Usage : ./app [loop]\n");
		return -1;
	}
	else
	{
		u_loop = atoi(argv[1]);
	}

    /* print app mode */
    handler_print_app_mode();

    /* Initialize the enclave */
    if(app_init_enclave() < 0)
    {
        printf("Enter a character before exit ...\n");
        getchar();
        return -1;
    }

    /* RDTSCP */
    cycle = rdtscp_test1(global_eid, u_loop);
    printf("Run Cycle(HW) -> %lu\n\n",cycle);

//    /* hello world */
//    cycle = helloworld(global_eid);
//    printf("\nRun Cycle(HW) = %lu\n\n",cycle);
//
//    /* lazy syscall */
//    ret = lazy_syscall(global_eid);
//    if(ret==0)
//    { printf("LAZY System Call Success -> [App]\n"); }
//    else
//    { printf("LAZY System Call fail -> [App]\n"); }
//    printf("LAZY System Call return : %d\n\n", ret);

    /* Destroy the enclave */
    if(sgx_destroy_enclave(global_eid) < 0)
    {
        printf("EXIT -> LAZY Enclave unsuccessfully returned.\n");
        return -1;
    }

    printf("EXIT -> LAZY Enclave successfully returned.\n");

//    printf("Enter a character before exit ...\n");
//    getchar();
    return 0;
}
/* main end */
