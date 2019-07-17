//
// Created by moe on 17.07.19.
//

#ifndef SGX_APPSBENCH_BASEAPP_H
#define SGX_APPSBENCH_BASEAPP_H


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <libgen.h>
#include <pthread.h>
#include <chrono>
#include <csignal>
#include <signal.h>

#ifndef TRUE
# define TRUE 1
#endif

#ifndef FALSE
# define FALSE 0
#endif

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define timeNow() std::chrono::high_resolution_clock::now()
#define duration(a) std::chrono::duration_cast<std::chrono::seconds>(a).count()



#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif


#endif //SGX_APPSBENCH_BASEAPP_H
