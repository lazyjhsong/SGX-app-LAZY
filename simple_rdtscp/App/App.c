//
// Created by jhsong on 18. 1. 26.
//

/* user h */
#include "App.h"

/* ocall func begin */
void ocall_print(const char* str)
{
    printf("%s",str);
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

void ocall_in_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*App_int_tmp) = (*var);
	printf("[%d,%d,%d] <- [A]ocall_in\n",(*var), (*App_int_tmp), (*App_int_var));
#endif
}

void ocall_out_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*var) = (*App_int_var);
	printf("[%d,%d,%d] <- [A]ocall_out\n",(*var), (*App_int_tmp), (*App_int_var));
#endif
}

void ocall_inout_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*App_int_tmp) = (*var);
	//printf("[%d,%d,%d] <- [A]ocall_inout(before)\n",(*var), (*App_int_tmp), (*App_int_var));
	(*var) = (*App_int_var);
	printf("[%d,%d,%d] <- [A]ocall_inout(after)\n",(*var), (*App_int_tmp), (*App_int_var));
#endif
}

void ocall_in_pass_rdtscp(char* var, size_t size)
{
	App_char_ptr = var;

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_in_pass\n", var[0], var[size-1], App_char_ptr[0], App_char_ptr[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_out_pass_rdtscp(char* var, size_t size)
{
#ifdef LAZYPDEBUG
	memset(var,APPCHARVAR,size);
#endif

	var = App_char_var;

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_out_pass\n", var[0], var[size-1], App_char_ptr[0], App_char_ptr[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_inout_pass_rdtscp(char* var, size_t size)
{
#ifdef LAZYPDEBUG
	memset(var,APPCHARVAR,size);
#endif

	App_char_ptr = var;
	var = App_char_var;

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_inout_pass\n", var[0], var[size-1], App_char_ptr[0], App_char_ptr[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_in_set_rdtscp(char* var, size_t size)
{
	memset(App_char_tmp,var[0],size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_in_set\n", var[0], var[size-1], App_char_tmp[0], App_char_tmp[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_out_set_rdtscp(char* var, size_t size)
{
	memset(var,App_char_var[0],size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_out_set\n", var[0], var[size-1], App_char_tmp[0], App_char_tmp[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_inout_set_rdtscp(char* var, size_t size)
{
	memset(App_char_tmp,var[0],size);
	memset(var,App_char_var[0],size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_in_set\n", var[0], var[size-1], App_char_tmp[0], App_char_tmp[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_in_cp_rdtscp(char* var, size_t size)
{
	memcpy(App_char_tmp, var, sizeof(char)*size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_in_cp\n", var[0], var[size-1], App_char_tmp[0], App_char_tmp[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_out_cp_rdtscp(char* var, size_t size)
{
	memcpy(var, App_char_var, sizeof(char)*size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_out\n", var[0], var[size-1], App_char_tmp[0], App_char_tmp[size-1], App_char_var[0], App_char_var[size-1]);
#endif
}

void ocall_inout_cp_rdtscp(char* var, size_t size)
{
	memcpy(App_char_tmp, var, sizeof(char)*size);
//	/* LAZY print debug */
//#ifdef LAZYPDEBUG
//	//memcpy(App_char_tmp, var, sizeof(char)*size);
//	//printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_inout(before)\n", var[0], var[size-1], App_char_tmp[0], App_char_tmp[size-1], App_char_var[0], App_char_var[size-1]);
//#endif

	memcpy(var, App_char_var, sizeof(char)*size);

#ifdef LAZYPDEBUG
	printf("[%c-%c,%c-%c,%c-%c] <- [A]ocall_inout(after)\n", var[0], var[size-1], App_char_tmp[0], App_char_tmp[size-1], App_char_var[0], App_char_var[size-1]);
#endif
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

void app_setup_var(sgx_enclave_id_t id, size_t App_size, int App_loop, int App_warm)
{
	test_setup_var(id, App_size, App_loop, App_warm);
}

void app_reset_int_tmp(sgx_enclave_id_t id)
{
	test_reset_int_tmp(id);
}

void app_reset_char_tmp(sgx_enclave_id_t id, size_t App_size)
{
	test_reset_char_tmp(id, App_size);
}

void app_free_var(sgx_enclave_id_t id)
{
	test_free_var(id);
}
/* user func end */

/* main begin */
int main(int argc, char *argv[])
{
    /* user var */
    int ret=0, App_loop=0, App_warm=0, App_size=0;
    uint64_t cycles_ecall_in=0, cycles_ecall_out=0, cycles_ecall_inout=0,
    		cycles_ocall_in=0, cycles_ocall_out=0, cycles_ocall_inout=0,
			cycles_ecall_in_pass=0, cycles_ecall_out_pass=0, cycles_ecall_inout_pass=0,
			cycles_ocall_in_pass=0, cycles_ocall_out_pass=0, cycles_ocall_inout_pass=0,
			cycles_ecall_in_set=0, cycles_ecall_out_set=0, cycles_ecall_inout_set=0,
			cycles_ocall_in_set=0, cycles_ocall_out_set=0, cycles_ocall_inout_set=0,
			cycles_ecall_in_cp=0, cycles_ecall_out_cp=0, cycles_ecall_inout_cp=0,
			cycles_ocall_in_cp=0, cycles_ocall_out_cp=0, cycles_ocall_inout_cp=0;

    /* argv */
	if(argc == 1)
	{
		App_warm = WARM;
		App_loop = LOOP;
		App_size = (size_t)VAR_SIZE;


	}
	else if(argc == 4)
	{
		App_warm = atoi(argv[3]);
		App_loop = atoi(argv[2]);
		App_size = (size_t)atoi(argv[1]);
		if((App_warm < 1) || (App_loop < 1) || (App_size < 1))
		{
			printf("\nsize, loop, warm < 1\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		printf("\nusage: ./app or ./app size loop warm\n");
		exit(EXIT_FAILURE);
	}

    /* print app mode */
    handler_print_app_mode();

    /* Initialize the enclave */
    if(app_init_enclave() < 0)
    {
    	printf("\nEXIT -> LAZY Enclave unsuccessfully initialized.\n");
    	exit(EXIT_FAILURE);
    }

    /* Ecall/Ocall TEST RDTSCP begin */
    app_setup_var(global_eid, App_size, App_loop, App_warm);

#ifdef TESTINTPASS
    printf("\n[TEST] -> INT PASS\n");

    cycles_ecall_in = test_ecall_in_rdtscp(global_eid);
#ifndef LAZYPDEBUG
    printf("Run Cycle[Ecall_IN] -> %lu\n",cycles_ecall_in);
#endif

    cycles_ecall_out = test_ecall_out_rdtscp(global_eid);
#ifndef LAZYPDEBUG
    printf("Run Cycle[Ecall_OUT] -> %lu\n",cycles_ecall_out);
#endif

    cycles_ecall_inout = test_ecall_inout_rdtscp(global_eid);
#ifndef LAZYPDEBUG
    printf("Run Cycle[Ecall_INOUT] -> %lu\n",cycles_ecall_inout);
#endif

    cycles_ocall_in = test_ocall_in_rdtscp(global_eid);
#ifndef LAZYPDEBUG
    printf("Run Cycle[Ocall_IN] -> %lu\n",cycles_ocall_in);
#endif

    cycles_ocall_out = test_ocall_out_rdtscp(global_eid);
#ifndef LAZYPDEBUG
    printf("Run Cycle[Ocall_OUT] -> %lu\n",cycles_ocall_out);
#endif
	cycles_ocall_inout = test_ocall_inout_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_INOUT] -> %lu\n",cycles_ocall_inout);
#endif
#endif

#ifdef TESTCHARPASS
	printf("\n[TEST] -> CHAR PASS\n");

	cycles_ecall_in_pass = test_ecall_in_pass_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_IN_PASS] -> %lu\n",cycles_ecall_in_pass);
#endif

	cycles_ecall_out_pass = test_ecall_out_pass_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_OUT_PASS] -> %lu\n",cycles_ecall_out_pass);
#endif

	cycles_ecall_inout_pass = test_ecall_inout_pass_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_INOUT_PASS] -> %lu\n",cycles_ecall_inout_pass);
#endif

	cycles_ocall_in_pass = test_ocall_in_pass_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_IN_PASS] -> %lu\n",cycles_ocall_in_pass);
#endif

	cycles_ocall_out_pass = test_ocall_out_pass_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_OUT_PASS] -> %lu\n",cycles_ocall_out_pass);
#endif

	cycles_ocall_inout_pass = test_ocall_inout_pass_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_INOUT_PASS] -> %lu\n",cycles_ocall_inout_pass);
#endif
#endif

#ifdef TESTCHARSET
	printf("\n[TEST] -> CHAR SET\n");

	cycles_ecall_in_set = test_ecall_in_set_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_IN_SET] -> %lu\n",cycles_ecall_in_set);
#endif

	cycles_ecall_out_set = test_ecall_out_set_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_OUT_SET] -> %lu\n",cycles_ecall_out_set);
#endif

	cycles_ecall_inout_set = test_ecall_inout_set_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_INOUT_SET] -> %lu\n",cycles_ecall_inout_set);
#endif

	cycles_ocall_in_set = test_ocall_in_set_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_IN_SET] -> %lu\n",cycles_ocall_in_set);
#endif

	cycles_ocall_out_set = test_ocall_out_set_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_OUT_SET] -> %lu\n",cycles_ocall_out_set);
#endif

	cycles_ocall_inout_set = test_ocall_inout_set_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_INOUT_SET] -> %lu\n",cycles_ocall_inout_set);
#endif
#endif

#ifdef TESTCHARCP
	printf("\n[TEST] -> CHAR CP\n");

	cycles_ecall_in_cp = test_ecall_in_cp_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_IN_CP] -> %lu\n",cycles_ecall_in_cp);
#endif

	cycles_ecall_out_cp = test_ecall_out_cp_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_OUT_CP] -> %lu\n",cycles_ecall_out_cp);
#endif

	cycles_ecall_inout_cp = test_ecall_inout_cp_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ecall_INOUT_CP] -> %lu\n",cycles_ecall_inout_cp);
#endif

	cycles_ocall_in_cp = test_ocall_in_cp_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_IN_CP] -> %lu\n",cycles_ocall_in_cp);
#endif

	cycles_ocall_out_cp = test_ocall_out_cp_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_OUT_CP] -> %lu\n",cycles_ocall_out_cp);
#endif

	cycles_ocall_inout_cp = test_ocall_inout_cp_rdtscp(global_eid);
#ifndef LAZYPDEBUG
	printf("Run Cycle[Ocall_INOUT_CP] -> %lu\n",cycles_ocall_inout_cp);
#endif
#endif

	app_free_var(global_eid);
    /* Ecall/Ocall TEST RDTSCP end */

    /* Destroy the enclave */
    if(sgx_destroy_enclave(global_eid) < 0)
    {
        printf("\nEXIT -> LAZY Enclave unsuccessfully returned.\n");
        exit(EXIT_FAILURE);
    }

    printf("\nEXIT -> LAZY Enclave successfully returned.\n");

//    printf("Enter a character before exit ...\n");
//    getchar();
    exit(EXIT_SUCCESS);
}
/* main end */
