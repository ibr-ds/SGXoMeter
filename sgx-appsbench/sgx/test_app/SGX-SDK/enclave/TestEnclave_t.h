#ifndef TESTENCLAVE_T_H__
#define TESTENCLAVE_T_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include "sgx_edger8r.h" /* for sgx_ocall etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

void new_thread_func(void);
void ecall_start_bench(void);
void ecall_pause_bench(void);
void ecall_stop_bench(void);
void ecall_cleanup_bench(void);
void ecall_run_bench(int test_id, int thread_id);
void ecall_run_bench_with_transitions(int test_id, int thread_id);
void ecall_set_config(uint64_t** ctr, void* globalConfig);

sgx_status_t SGX_CDECL uprint(const char* str);
sgx_status_t SGX_CDECL ocallMalloc(void** retval, size_t size);
sgx_status_t SGX_CDECL ocallFree(void* buffer);
sgx_status_t SGX_CDECL usgx_exit(int reason);
sgx_status_t SGX_CDECL ucreate_thread(int* retval);
sgx_status_t SGX_CDECL u_sgxssl_ftime(void* timeptr, uint32_t timeb_len);
sgx_status_t SGX_CDECL sgx_oc_cpuidex(int cpuinfo[4], int leaf, int subleaf);
sgx_status_t SGX_CDECL sgx_thread_wait_untrusted_event_ocall(int* retval, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_untrusted_event_ocall(int* retval, const void* waiter);
sgx_status_t SGX_CDECL sgx_thread_setwait_untrusted_events_ocall(int* retval, const void* waiter, const void* self);
sgx_status_t SGX_CDECL sgx_thread_set_multiple_untrusted_events_ocall(int* retval, const void** waiters, size_t total);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
