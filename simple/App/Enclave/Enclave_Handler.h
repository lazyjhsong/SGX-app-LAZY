//
// Created by jhsong on 18. 1. 27.
//

#ifndef SIMPLE_ENCLAVE_HANDLER_H
#define SIMPLE_ENCLAVE_HANDLER_H

/* lib h */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <stdarg.h>

/* sgx h */
#include "sgx_error.h"       /* sgx_status_t */
#include "sgx_eid.h"     /* sgx_enclave_id_t */
#include "sgx_urts.h"

/* def T/F */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* def file */
#define TOKEN_PATH          "/home/jhsong/"
#define TOKEN_FILENAME      "enclave.token"
#define ENCLAVE_FILENAME    "enclave.signed.so"
#define MAX_PATH            FILENAME_MAX

/* global enclave id */
extern sgx_enclave_id_t global_eid;    /* global enclave id */

/* sgx type */
typedef struct _sgx_errlist_t {
    sgx_status_t err;
    const char *msg;
    const char *sug; /* Suggestion */
} sgx_errlist_t;

/* user func */
void handler_print_error_msg(sgx_status_t);
int handler_init_enclave(void);
int handler_destroy_enclave(sgx_enclave_id_t);

#endif //SIMPLE_ENCLAVE_HANDLER_H
