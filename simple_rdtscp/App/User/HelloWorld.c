//
// Created by jhsong on 18. 1. 26.
//

#include "HelloWorld.h"

uint64_t helloworld(sgx_enclave_id_t id)
{
	/* RDTSCP var */
	unsigned int junk = 0;
	register uint64_t start=0, end=0, cycle=0;

	/* user var */
	const char str[] = "\nHelloWorld!";

	/* warm */
//	start = __rdtscp( & junk);
//	start = __rdtscp( & junk);

	/* RDTSCP start */
//	start = __rdtscp( & junk);

	/* Ecall */
    ecall_print_trace(id, str);

    /* RDTSCP end */
//    end = __rdtscp( & junk);

    /* cycle */
//    cycle = end - start;

    return cycle;
}
