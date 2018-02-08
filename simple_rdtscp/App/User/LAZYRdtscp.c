/*
 * LAZYRdtscp.c
 * Created by jhsong on Feb 5, 2018
 */

#include "LAZYRdtscp.h"

int* App_int_var;
int* App_int_dummy;
int* App_int_tmp;
char* App_char_var;
char* App_char_tmp;
char* App_char_ptr;
int T_loop=0, T_warm=0;
size_t T_size=0;

/* setup var */
void test_setup_var(sgx_enclave_id_t id, size_t App_size, int App_loop, int App_warm)
{
	T_loop = App_loop;
	T_warm = App_warm;
	T_size = App_size;

	printf("TEST_VAR_SIZE -> %lu\n", T_size);
	printf("TEST_LOOP_COUNT -> %d\n", T_loop);
	printf("TEST_WARM_COUNT -> %d\n", T_warm);

	App_int_var = (int*)malloc(sizeof(int));
	if(App_int_var==NULL)
	{
		perror("\nApp_int_var malloc failed\n");
		exit(EXIT_FAILURE);
	}
	App_int_dummy = (int*)malloc(sizeof(int));
	if(App_int_dummy==NULL)
	{
		perror("\nApp_int_dummy malloc failed\n");
		exit(EXIT_FAILURE);
	}
	App_int_tmp = (int*)malloc(sizeof(int));
	if(App_int_tmp==NULL)
	{
		perror("\nApp_int_tmp malloc failed\n");
		exit(EXIT_FAILURE);
	}

	App_char_var = (char*)malloc(sizeof(char)*App_size);
	if(App_char_var==NULL)
	{
		perror("\nApp_char_var malloc failed\n");
		exit(EXIT_FAILURE);
	}
	App_char_tmp = (char*)malloc(sizeof(char)*App_size);
	if(App_char_tmp==NULL)
	{
		perror("\nApp_char_tmp malloc failed\n");
		exit(EXIT_FAILURE);
	}

	(*App_int_var) = APPINTVAR;
	(*App_int_dummy) = APPINTDUMMY;
	(*App_int_tmp) = APPINTTMP;
	memset(App_char_var,APPCHARVAR,sizeof(char)*App_size);
	memset(App_char_tmp,APPCHARTMP,sizeof(char)*App_size);
	App_char_ptr = App_char_tmp;

	ecall_setup_var(id, &T_size);
}

void test_reset_int_tmp(sgx_enclave_id_t id)
{
	(*App_int_tmp) = APPINTTMP;
	ecall_reset_int_tmp(id);
}

void test_reset_char_tmp(sgx_enclave_id_t id, size_t App_size)
{
	memset(App_char_tmp,APPCHARTMP,sizeof(char)*App_size);
	App_char_ptr = App_char_tmp;
	ecall_reset_char_tmp(id, &T_size);
}

void test_free_var(sgx_enclave_id_t id)
{
	free(App_int_var);
	free(App_int_dummy);
	free(App_int_tmp);
	free(App_char_var);
	free(App_char_tmp);

	ecall_free_var(id);
}

/* RDTSCP test begin */
uint64_t test_ecall_in_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_int_tmp(id);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_in_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	test_reset_int_tmp(id);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ecall_in(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall IN */
	    ecall_in_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ecall_in(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ecall_out_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_int_tmp(id);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_out_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	test_reset_int_tmp(id);

	/* loop */
	for(i=0;i<T_loop;i++)
	{
	    /* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*,%d,%d] <- [T]test_ecall_out(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall OUT */
	    ecall_out_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

	    /* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*,%d,%d] <- [T]test_ecall_out(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ecall_inout_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_int_tmp(id);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_inout_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	test_reset_int_tmp(id);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ecall_inout(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall INOUT */
	    ecall_inout_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

	    /* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*,%d,%d] <- [T]test_ecall_inout(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_in_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_in_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_in_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_in_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
	    ecall_ocall_in_rdtscp_dummy(id, App_int_tmp);

	    /* RDTSCP end */
	    end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_in_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_in(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall IN */
	    ecall_ocall_in_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_in(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_out_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_out_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_out_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_out_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
	    ecall_ocall_out_rdtscp_dummy(id, App_int_tmp);

	    /* RDTSCP end */
	    end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_out_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_out(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall OUT */
	    ecall_ocall_out_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_out(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_inout_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_inout_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_inout_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_inout_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
	    ecall_ocall_inout_rdtscp_dummy(id, App_int_tmp);

	    /* RDTSCP end */
	    end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_inout_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_inout(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall INOUT */
	    ecall_ocall_inout_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*,%d,%d] <- [T]test_ocall_inout(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ecall_in_pass_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_in_pass_rdtscp(id, App_char_ptr, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_in_pass(before)\n",App_char_ptr[0], App_char_ptr[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall IN PASS */
	    ecall_in_pass_rdtscp(id, App_char_ptr, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_in_pass(after)\n",App_char_ptr[0], App_char_ptr[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ecall_out_pass_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_out_pass_rdtscp(id, App_char_ptr, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_out_pass(before)\n",App_char_ptr[0], App_char_ptr[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall OUT PASS */
	    ecall_out_pass_rdtscp(id, App_char_ptr, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_out_pass(after)\n",App_char_ptr[0], App_char_ptr[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ecall_inout_pass_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_inout_pass_rdtscp(id, App_char_ptr, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_inout_pass(before)\n",App_char_ptr[0], App_char_ptr[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall INOUT PASS */
	    ecall_inout_pass_rdtscp(id, App_char_ptr, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_inout_pass(after)\n",App_char_ptr[0], App_char_ptr[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ocall_in_pass_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_in_pass_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_in_pass_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_pass_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
		ecall_ocall_in_pass_rdtscp_dummy(id, App_int_tmp);

		/* RDTSCP end */
		end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_pass_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_pass(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall IN PASS */
		ecall_ocall_in_pass_rdtscp(id, App_int_tmp);

		/* RDTSCP end */
		end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_pass(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ocall_out_pass_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_out_pass_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_out_pass_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_pass_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
		ecall_ocall_out_pass_rdtscp_dummy(id, App_int_tmp);

		/* RDTSCP end */
		end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_pass_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_pass(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall OUT PASS */
		ecall_ocall_out_pass_rdtscp(id, App_int_tmp);

		/* RDTSCP end */
		end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_pass(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ocall_inout_pass_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_inout_pass_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_inout_pass_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_pass_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
		ecall_ocall_inout_pass_rdtscp_dummy(id, App_int_tmp);

		/* RDTSCP end */
		end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_pass_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_pass(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall INOUT PASS */
		ecall_ocall_inout_pass_rdtscp(id, App_int_tmp);

		/* RDTSCP end */
		end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_pass(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ecall_in_set_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_in_set_rdtscp(id, App_char_tmp, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_in_set(before)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall IN SET */
	    ecall_in_set_rdtscp(id, App_char_tmp, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_in_set(after)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ecall_out_set_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_out_set_rdtscp(id, App_char_tmp, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_out_set(before)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall OUT SET */
	    ecall_out_set_rdtscp(id, App_char_tmp, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_out_set(after)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ecall_inout_set_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_inout_set_rdtscp(id, App_char_tmp, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_inout_set(before)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall INOUT SET */
	    ecall_inout_set_rdtscp(id, App_char_tmp, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_inout_set(after)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
uint64_t test_ocall_in_set_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_in_set_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_in_set_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_set_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
		ecall_ocall_in_set_rdtscp_dummy(id, App_int_tmp);

		/* RDTSCP end */
		end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_set_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_set(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall IN SET */
		ecall_ocall_in_set_rdtscp(id, App_int_tmp);

		/* RDTSCP end */
		end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_set(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_out_set_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_out_set_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_out_set_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_set_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
		ecall_ocall_out_set_rdtscp_dummy(id, App_int_tmp);

		/* RDTSCP end */
		end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_set_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_set(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall OUT SET */
		ecall_ocall_out_set_rdtscp(id, App_int_tmp);

		/* RDTSCP end */
		end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_set(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_inout_set_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_inout_set_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_inout_set_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_set_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
		ecall_ocall_inout_set_rdtscp_dummy(id, App_int_tmp);

		/* RDTSCP end */
		end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_set_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_set(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall IN PASS */
		ecall_ocall_inout_set_rdtscp(id, App_int_tmp);

		/* RDTSCP end */
		end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_set(after)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* cycle */
		cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ecall_in_cp_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_in_cp_rdtscp(id, App_char_tmp, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_in_cp(before)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall IN */
	    ecall_in_cp_rdtscp(id, App_char_tmp, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_in_cp(after)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ecall_out_cp_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_out_cp_rdtscp(id, App_char_tmp, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_out_cp(before)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall OUT */
	    ecall_out_cp_rdtscp(id, App_char_tmp, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_out_cp(after)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ecall_inout_cp_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;

	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_inout_cp_rdtscp(id, App_char_tmp, T_size);
		__rdtscp( & junk);
	}
#endif

	test_reset_char_tmp(id, T_size);

	/* loop */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_inout_cp(before)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall INOUT */
	    ecall_inout_cp_rdtscp(id, App_char_tmp, T_size);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	    printf("[*-*,%c-%c,%c-%c] <- [T]test_ecall_inout_cp(after)\n",App_char_tmp[0], App_char_tmp[T_size-1], App_char_var[0], App_char_var[T_size-1]);
#endif

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_in_cp_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_in_cp_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_in_cp_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_cp_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall IN */
	    ecall_ocall_in_cp_rdtscp_dummy(id, App_int_tmp);

	    /* RDTSCP end */
	    end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_cp_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_cp(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall IN -> Ocall IN */
	    ecall_ocall_in_cp_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_in_cp(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_out_cp_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_out_cp_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_out_cp_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_cp_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall OUT */
	    ecall_ocall_out_cp_rdtscp_dummy(id, App_int_tmp);

	    /* RDTSCP end */
	    end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_cp_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_cp(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall OUT -> Ocall OUT */
	    ecall_ocall_out_cp_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_out_cp(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}

uint64_t test_ocall_inout_cp_rdtscp(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	uint64_t start1=0, end1=0, cycle1=0, cycle=0,
			start2=0, end2=0, cycle2=0, cycle_avg=0;

	/* user var */
	int i;

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* warm */
#ifdef LAZYWARM
	for(i=0;i<T_warm;i++)
	{
		__rdtscp( & junk);
		ecall_ocall_inout_cp_rdtscp_dummy(id, App_int_tmp);
		ecall_ocall_inout_cp_rdtscp(id, App_int_tmp);
		__rdtscp( & junk);
	}
#endif

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall only */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_cp_dummy(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start1 = __rdtscp( & junk);

		/* Ecall INOUT */
	    ecall_ocall_inout_cp_rdtscp_dummy(id, App_int_tmp);

	    /* RDTSCP end */
	    end1 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_cp_dummy(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle1 += (end1 - start1);
	}

	(*App_int_tmp) = (*App_int_dummy);
	test_reset_char_tmp(id, T_size);

	/* loop ecall -> ocall */
	for(i=0;i<T_loop;i++)
	{

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_cp(before)\n",(*App_int_tmp), (*App_int_var));
#endif

		/* RDTSCP start */
		start2 = __rdtscp( & junk);

		/* Ecall INOUT -> Ocall INOUT */
	    ecall_ocall_inout_cp_rdtscp(id, App_int_tmp);

	    /* RDTSCP end */
	    end2 = __rdtscp( & junk);

		/* LAZY print debug */
#ifdef LAZYPDEBUG
		printf("[0,%d,%d] <- [T]test_ocall_inout_cp(after)\n",(*App_int_tmp), (*App_int_var));
#endif

	    /* cycle */
	    cycle2 += (end2 - start2);
	}
	cycle = cycle2 - cycle1;
	cycle_avg = (float)cycle / T_loop;
	return cycle_avg;
}
/* RDTSCP test end */
