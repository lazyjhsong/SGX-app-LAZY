/*
 * envdefine.h
 * Created by jhsong on Feb 7, 2018
 */

#ifndef APP_INCLUDE_ENVDEFINE_H_
#define APP_INCLUDE_ENVDEFINE_H_

/* define */
#define APPINTVAR 1
#define APPINTDUMMY 5
#define APPINTTMP 2
#define APPCHARVAR 'A'
#define APPCHARTMP 'a'

#define ENCLAVEINTVAR 9
#define ENCLAVEINTTMP 8
#define ENCLAVECHARVAR 'E'
#define ENCLAVECHARTMP 'e'

//#define LAZYPDEBUG

#ifdef LAZYPDEBUG
#define LOOP 1
#define WARM 0
#define VAR_SIZE 1024*1

#else
#define LAZYWARM
#define LOOP 50000
#define WARM 10
#define VAR_SIZE 1024*128
#endif

#define TESTINTPASS
#define TESTCHARPASS
#define TESTCHARSET
#define TESTCHARCP

#endif /* APP_INCLUDE_ENVDEFINE_H_ */
