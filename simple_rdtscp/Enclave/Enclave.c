//
// Created by jhsong on 18. 1. 27.
//

/* user h */
#include "Enclave.h"

int* Enclave_int_var;
int* Enclave_int_tmp;
char* Enclave_char_var;
char* Enclave_char_tmp;
char* Enclave_char_ptr;
size_t Enclave_size;


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

void ecall_setup_var(size_t* size)
{
	Enclave_int_var=(int*)malloc(sizeof(int));
	if(Enclave_int_var==NULL)
	{
		return;
	}
	Enclave_int_tmp=(int*)malloc(sizeof(int));
	if(Enclave_int_tmp==NULL)
	{
		return;
	}

	Enclave_char_var=(char*)malloc(sizeof(char)*(*size));
	if(Enclave_char_var==NULL)
	{
		return;
	}
	Enclave_char_tmp=(char*)malloc(sizeof(char)*(*size));
	if(Enclave_char_tmp==NULL)
	{
		return;
	}

	Enclave_size = (*size);

	(*Enclave_int_var) = ENCLAVEINTVAR;
	(*Enclave_int_tmp) = ENCLAVEINTTMP;
	memset(Enclave_char_var,ENCLAVECHARVAR,sizeof(char)*(*size));
	memset(Enclave_char_tmp,ENCLAVECHARTMP,sizeof(char)*(*size));
	Enclave_char_ptr = Enclave_char_tmp;
}

void ecall_reset_int_tmp()
{
	(*Enclave_int_tmp) = ENCLAVEINTTMP;
}

void ecall_reset_char_tmp(size_t* size)
{
	memset(Enclave_char_tmp,ENCLAVECHARTMP,sizeof(char)*(*size));
	Enclave_char_ptr = Enclave_char_tmp;
}

void ecall_free_var()
{
	free(Enclave_int_var);
	free(Enclave_int_tmp);

	free(Enclave_char_var);
	free(Enclave_char_tmp);
}

void ecall_in_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	enclave_printf("[%d,%d,%d] <- [E]ecall_in\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
#endif

}

void ecall_out_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*var) = (*Enclave_int_var);
	enclave_printf("[%d,%d,%d] <- [E]ecall_out\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
#endif

}

void ecall_inout_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ecall_inout(before)\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*var) = (*Enclave_int_var);
	enclave_printf("[%d,%d,%d] <- [E]ecall_inout\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
#endif

}

void ecall_ocall_in_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	enclave_printf("[%d,%d,%d] <- [E]ocall_in(before)\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif

	ocall_in_rdtscp(Enclave_int_tmp);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%d,%d,%d] <- [E]ocall_in(after)\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
#endif
}

void ecall_ocall_out_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	enclave_printf("[%d,%d,%d] <- [E]ocall_out(before)\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif

	ocall_out_rdtscp(Enclave_int_tmp);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%d,%d,%d] <- [E]ocall_out(after)\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
#endif

}
void ecall_ocall_inout_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	enclave_printf("[%d,%d,%d] <- [E]ocall_inout(before)\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif

	ocall_inout_rdtscp(Enclave_int_tmp);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%d,%d,%d] <- [E]ocall_inout(after)\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
#endif
}

void ecall_ocall_in_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	enclave_printf("[%d,%d,%d] <- [E]ocall_in_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}
void ecall_ocall_out_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	enclave_printf("[%d,%d,%d] <- [E]ocall_out_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif

}
void ecall_ocall_inout_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	enclave_printf("[%d,%d,%d] <- [E]ocall_inout_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}

void ecall_in_pass_rdtscp(char* var, size_t size)
{
	Enclave_char_ptr = var;
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%c-%c,%c-%c,%c-%c] <- [E]ecall_in_pass\n",var[0], var[size-1], Enclave_char_ptr[0], Enclave_char_ptr[size-1], Enclave_char_var[0], Enclave_char_var[size-1]);
#endif
}

void ecall_out_pass_rdtscp(char* var, size_t size)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	memset(var,ENCLAVECHARVAR,size);
#endif

	var = Enclave_char_var;

		/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%c-%c,%c-%c,%c-%c] <- [E]ecall_out_pass\n",var[0], var[size-1], Enclave_char_ptr[0], Enclave_char_ptr[size-1], Enclave_char_var[0], Enclave_char_var[size-1]);
#endif
}

void ecall_inout_pass_rdtscp(char* var, size_t size)
{
#ifdef LAZYPDEBUG
	memset(var,ENCLAVECHARVAR,size);
#endif

	Enclave_char_ptr = var;
	var = Enclave_char_var;

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%c-%c,%c-%c,%c-%c] <- [E]ecall_inout_pass\n",var[0], var[size-1], Enclave_char_ptr[0], Enclave_char_ptr[size-1], Enclave_char_var[0], Enclave_char_var[size-1]);
#endif
}

void ecall_ocall_in_pass_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_in_cp\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_in_pass(before)\n", Enclave_char_ptr[0], Enclave_char_ptr[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif

	ocall_in_pass_rdtscp(Enclave_char_ptr, Enclave_size);

#ifdef LAZYPDEBUG
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_in_pass(after)\n", Enclave_char_ptr[0], Enclave_char_ptr[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif
}

void ecall_ocall_out_pass_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_in_cp\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_out_pass(before)\n", Enclave_char_ptr[0], Enclave_char_ptr[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif

	ocall_out_pass_rdtscp(Enclave_char_ptr, Enclave_size);

#ifdef LAZYPDEBUG
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_out_pass(after)\n", Enclave_char_ptr[0], Enclave_char_ptr[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif
}

void ecall_ocall_inout_pass_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_in_cp\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_inout_pass(before)\n", Enclave_char_ptr[0], Enclave_char_ptr[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif

	ocall_inout_pass_rdtscp(Enclave_char_ptr, Enclave_size);

#ifdef LAZYPDEBUG
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_inout_pass(after)\n", Enclave_char_ptr[0], Enclave_char_ptr[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif
}

void ecall_ocall_in_pass_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_in_pass_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}

void ecall_ocall_out_pass_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_out_pass_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}

void ecall_ocall_inout_pass_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_inout_pass_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}

void ecall_in_set_rdtscp(char* var, size_t size)
{}

void ecall_out_set_rdtscp(char* var, size_t size)
{}

void ecall_inout_set_rdtscp(char* var, size_t size)
{}

void ecall_ocall_in_set_rdtscp(int* var)
{}

void ecall_ocall_out_set_rdtscp(int* var)
{}

void ecall_ocall_inout_set_rdtscp(int* var)
{}

void ecall_ocall_in_set_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_in_set_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}

void ecall_ocall_out_set_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_out_set_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}

void ecall_ocall_inout_set_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_inout_set_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}

void ecall_in_cp_rdtscp(char* var, size_t size)
{
	memcpy(Enclave_char_tmp, var, sizeof(char)*size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%c-%c,%c-%c,%c-%c] <- [E]ecall_in_cp\n", var[0], var[size-1], Enclave_char_tmp[0], Enclave_char_tmp[size-1], Enclave_char_var[0], Enclave_char_var[size-1]);
#endif
}

void ecall_out_cp_rdtscp(char* var, size_t size)
{
	memcpy(var, Enclave_char_var, sizeof(char)*size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%c-%c,%c-%c,%c-%c] <- [E]ecall_out_cp\n", var[0], var[size-1], Enclave_char_tmp[0], Enclave_char_tmp[size-1], Enclave_char_var[0], Enclave_char_var[size-1]);
#endif
}

void ecall_inout_cp_rdtscp(char* var, size_t size)
{
	memcpy(Enclave_char_tmp, var, sizeof(char)*size);
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	//memcpy(Enclave_char_tmp, var, sizeof(char)*size);
	//enclave_printf("[%c-%c,%c-%c,%c-%c] <- [E]ecall_inout_cp(before)\n", var[0], var[size-1], Enclave_char_tmp[0], Enclave_char_tmp[size-1], Enclave_char_var[0], Enclave_char_var[size-1]);
#endif

	memcpy(var, Enclave_char_var, sizeof(char)*size);

	/* LAZY print debug */
#ifdef LAZYPDEBUG
	enclave_printf("[%c-%c,%c-%c,%c-%c] <- [E]ecall_inout_cp\n", var[0], var[size-1], Enclave_char_tmp[0], Enclave_char_tmp[size-1], Enclave_char_var[0], Enclave_char_var[size-1]);
#endif
}

void ecall_ocall_in_cp_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_in_cp\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_in_cp(before)\n", Enclave_char_tmp[0], Enclave_char_tmp[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif

	ocall_in_cp_rdtscp(Enclave_char_tmp, Enclave_size);

#ifdef LAZYPDEBUG
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_in_cp(after)\n", Enclave_char_tmp[0], Enclave_char_tmp[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif
}
void ecall_ocall_out_cp_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_out_cp\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_out_cp(before)\n", Enclave_char_tmp[0], Enclave_char_tmp[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif

	ocall_out_cp_rdtscp(Enclave_char_tmp, Enclave_size);

#ifdef LAZYPDEBUG
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_out_cp(after)\n", Enclave_char_tmp[0], Enclave_char_tmp[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif
}
void ecall_ocall_inout_cp_rdtscp(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_inout_cp\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_inout_cp(after)\n", Enclave_char_tmp[0], Enclave_char_tmp[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif

	ocall_inout_cp_rdtscp(Enclave_char_tmp, Enclave_size);

#ifdef LAZYPDEBUG
	enclave_printf("[*-*,%c-%c,%c-%c] <- [E]ocall_inout_cp(after)\n", Enclave_char_tmp[0], Enclave_char_tmp[Enclave_size-1], Enclave_char_var[0], Enclave_char_var[Enclave_size-1]);
#endif
}
void ecall_ocall_in_cp_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_in_cp_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}
void ecall_ocall_out_cp_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_out_cp_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}
void ecall_ocall_inout_cp_rdtscp_dummy(int* var)
{
	/* LAZY print debug */
#ifdef LAZYPDEBUG
	(*Enclave_int_tmp) = (*var);
	//enclave_printf("[%d,%d,%d] <- [E]ocall_inout_cp_dummy\n",(*var), (*Enclave_int_tmp), (*Enclave_int_var));
	(*Enclave_int_tmp) = (*Enclave_int_var);
#endif
}
/* e call func end */

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


