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
/* ocall func end */

/* user func begin */
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
    /* var */
    int ret = 0;

    /* Initialize the enclave */
    if(app_init_enclave() < 0)
    {
        printf("Enter a character before exit ...\n");
        getchar();
        return -1;
    }
    else
    {
        printf("[App]Enclave initialization SUCCESS!\n");
    }

    /* do something in enclave begin */
    /* ~~~ */
    /* do something in enclave end */

    /* Destroy the enclave */
    if(sgx_destroy_enclave(global_eid) < 0)
    {
        printf("Enter a character before exit ...\n");
        getchar();
        return -1;
    }
    else
    {
        printf("[App]Enclave destruction SUCCESS!\n");
    }

    printf("Info: LAZY Enclave successfully returned.\n");

    printf("Enter a character before exit ...\n");
    getchar();
    return 0;
}
/* main end */