#ifndef TESTENCLAVE_U_H__
#define TESTENCLAVE_U_H__

#include <stdint.h>
#include <wchar.h>
#include <stddef.h>
#include <string.h>
#include "sgx_edger8r.h" /* for sgx_status_t etc. */


#include <stdlib.h> /* for size_t */

#define SGX_CAST(type, item) ((type)(item))

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UPRINT_DEFINED__
#define UPRINT_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, uprint, (const char* str));
#endif
#ifndef OCALLMALLOC_DEFINED__
#define OCALLMALLOC_DEFINED__
void* SGX_UBRIDGE(SGX_NOCONVENTION, ocallMalloc, (size_t size));
#endif
#ifndef OCALLFREE_DEFINED__
#define OCALLFREE_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, ocallFree, (void* buffer));
#endif
#ifndef USGX_EXIT_DEFINED__
#define USGX_EXIT_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, usgx_exit, (int reason));
#endif
#ifndef UCREATE_THREAD_DEFINED__
#define UCREATE_THREAD_DEFINED__
int SGX_UBRIDGE(SGX_NOCONVENTION, ucreate_thread, (void));
#endif
#ifndef U_SGXSSL_FTIME_DEFINED__
#define U_SGXSSL_FTIME_DEFINED__
void SGX_UBRIDGE(SGX_NOCONVENTION, u_sgxssl_ftime, (void* timeptr, uint32_t timeb_len));
#endif
#ifndef SGX_OC_CPUIDEX_DEFINED__
#define SGX_OC_CPUIDEX_DEFINED__
void SGX_UBRIDGE(SGX_CDECL, sgx_oc_cpuidex, (int cpuinfo[4], int leaf, int subleaf));
#endif
#ifndef SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_WAIT_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_wait_untrusted_event_ocall, (const void* self));
#endif
#ifndef SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
#define SGX_THREAD_SET_UNTRUSTED_EVENT_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_untrusted_event_ocall, (const void* waiter));
#endif
#ifndef SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SETWAIT_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_setwait_untrusted_events_ocall, (const void* waiter, const void* self));
#endif
#ifndef SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
#define SGX_THREAD_SET_MULTIPLE_UNTRUSTED_EVENTS_OCALL_DEFINED__
int SGX_UBRIDGE(SGX_CDECL, sgx_thread_set_multiple_untrusted_events_ocall, (const void** waiters, size_t total));
#endif

sgx_status_t new_thread_func(sgx_enclave_id_t eid);
sgx_status_t ecall_start_bench(sgx_enclave_id_t eid);
sgx_status_t ecall_pause_bench(sgx_enclave_id_t eid);
sgx_status_t ecall_stop_bench(sgx_enclave_id_t eid);
sgx_status_t ecall_cleanup_bench(sgx_enclave_id_t eid);
sgx_status_t ecall_run_bench(sgx_enclave_id_t eid, int test_id, int thread_id);
sgx_status_t ecall_run_bench_with_transitions(sgx_enclave_id_t eid, int test_id, int thread_id);
sgx_status_t ecall_set_config(sgx_enclave_id_t eid, uint64_t** ctr, void* globalConfig);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
