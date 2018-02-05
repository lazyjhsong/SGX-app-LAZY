/*
 * LAZYRdtscp.c
 * Created by jhsong on Feb 5, 2018
 */

#include "LAZYRdtscp.h"

uint64_t rdtscp_test1(sgx_enclave_id_t id, int loop)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	register uint64_t start=0, end=0, cycle=0, cycle_avg=0;

	/* user var */
	int i;
	int* val;
	int len=10;

	printf("RDTSCP_TEST1_Loop -> %d\n", loop);

	val = (int*)malloc(sizeof(int)*len);
	memset(val,0,sizeof(val));
	/* warm */
	start = __rdtscp( & junk);
	start = __rdtscp( & junk);

	/* loop */
	for(i=0;i<loop;i++)
	{
		/* RDTSCP start */
		start = __rdtscp( & junk);

		/* Ecall */
	    ecall_rdtscp_test1(id, val);

	    /* RDTSCP end */
	    end = __rdtscp( & junk);

	    /* cycle */
	    cycle += (end - start);
	}

	cycle_avg = (float)cycle / loop;
	return cycle_avg;
}
