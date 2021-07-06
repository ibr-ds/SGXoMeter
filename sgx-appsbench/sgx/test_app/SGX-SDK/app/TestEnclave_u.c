#include "TestEnclave_u.h"
#include <errno.h>

typedef struct ms_ecall_run_bench_t {
	int ms_test_id;
	int ms_thread_id;
} ms_ecall_run_bench_t;

typedef struct ms_ecall_run_bench_with_transitions_t {
	int ms_test_id;
	int ms_thread_id;
} ms_ecall_run_bench_with_transitions_t;

typedef struct ms_ecall_set_config_t {
	uint64_t** ms_ctr;
	void* ms_globalConfig;
} ms_ecall_set_config_t;

typedef struct ms_uprint_t {
	const char* ms_str;
} ms_uprint_t;

typedef struct ms_ocallMalloc_t {
	void* ms_retval;
	size_t ms_size;
} ms_ocallMalloc_t;

typedef struct ms_ocallFree_t {
	void* ms_buffer;
} ms_ocallFree_t;

typedef struct ms_usgx_exit_t {
	int ms_reason;
} ms_usgx_exit_t;

typedef struct ms_ucreate_thread_t {
	int ms_retval;
} ms_ucreate_thread_t;

typedef struct ms_u_sgxssl_ftime_t {
	void* ms_timeptr;
	uint32_t ms_timeb_len;
} ms_u_sgxssl_ftime_t;

typedef struct ms_sgx_oc_cpuidex_t {
	int* ms_cpuinfo;
	int ms_leaf;
	int ms_subleaf;
} ms_sgx_oc_cpuidex_t;

typedef struct ms_sgx_thread_wait_untrusted_event_ocall_t {
	int ms_retval;
	const void* ms_self;
} ms_sgx_thread_wait_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_set_untrusted_event_ocall_t {
	int ms_retval;
	const void* ms_waiter;
} ms_sgx_thread_set_untrusted_event_ocall_t;

typedef struct ms_sgx_thread_setwait_untrusted_events_ocall_t {
	int ms_retval;
	const void* ms_waiter;
	const void* ms_self;
} ms_sgx_thread_setwait_untrusted_events_ocall_t;

typedef struct ms_sgx_thread_set_multiple_untrusted_events_ocall_t {
	int ms_retval;
	const void** ms_waiters;
	size_t ms_total;
} ms_sgx_thread_set_multiple_untrusted_events_ocall_t;

static sgx_status_t SGX_CDECL TestEnclave_uprint(void* pms)
{
	ms_uprint_t* ms = SGX_CAST(ms_uprint_t*, pms);
	uprint(ms->ms_str);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_ocallMalloc(void* pms)
{
	ms_ocallMalloc_t* ms = SGX_CAST(ms_ocallMalloc_t*, pms);
	ms->ms_retval = ocallMalloc(ms->ms_size);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_ocallFree(void* pms)
{
	ms_ocallFree_t* ms = SGX_CAST(ms_ocallFree_t*, pms);
	ocallFree(ms->ms_buffer);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_usgx_exit(void* pms)
{
	ms_usgx_exit_t* ms = SGX_CAST(ms_usgx_exit_t*, pms);
	usgx_exit(ms->ms_reason);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_ucreate_thread(void* pms)
{
	ms_ucreate_thread_t* ms = SGX_CAST(ms_ucreate_thread_t*, pms);
	ms->ms_retval = ucreate_thread();

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_u_sgxssl_ftime(void* pms)
{
	ms_u_sgxssl_ftime_t* ms = SGX_CAST(ms_u_sgxssl_ftime_t*, pms);
	u_sgxssl_ftime(ms->ms_timeptr, ms->ms_timeb_len);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_sgx_oc_cpuidex(void* pms)
{
	ms_sgx_oc_cpuidex_t* ms = SGX_CAST(ms_sgx_oc_cpuidex_t*, pms);
	sgx_oc_cpuidex(ms->ms_cpuinfo, ms->ms_leaf, ms->ms_subleaf);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_sgx_thread_wait_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_wait_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_wait_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_wait_untrusted_event_ocall(ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_sgx_thread_set_untrusted_event_ocall(void* pms)
{
	ms_sgx_thread_set_untrusted_event_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_untrusted_event_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_untrusted_event_ocall(ms->ms_waiter);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_sgx_thread_setwait_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_setwait_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_setwait_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_setwait_untrusted_events_ocall(ms->ms_waiter, ms->ms_self);

	return SGX_SUCCESS;
}

static sgx_status_t SGX_CDECL TestEnclave_sgx_thread_set_multiple_untrusted_events_ocall(void* pms)
{
	ms_sgx_thread_set_multiple_untrusted_events_ocall_t* ms = SGX_CAST(ms_sgx_thread_set_multiple_untrusted_events_ocall_t*, pms);
	ms->ms_retval = sgx_thread_set_multiple_untrusted_events_ocall(ms->ms_waiters, ms->ms_total);

	return SGX_SUCCESS;
}

static const struct {
	size_t nr_ocall;
	void * table[11];
} ocall_table_TestEnclave = {
	11,
	{
		(void*)TestEnclave_uprint,
		(void*)TestEnclave_ocallMalloc,
		(void*)TestEnclave_ocallFree,
		(void*)TestEnclave_usgx_exit,
		(void*)TestEnclave_ucreate_thread,
		(void*)TestEnclave_u_sgxssl_ftime,
		(void*)TestEnclave_sgx_oc_cpuidex,
		(void*)TestEnclave_sgx_thread_wait_untrusted_event_ocall,
		(void*)TestEnclave_sgx_thread_set_untrusted_event_ocall,
		(void*)TestEnclave_sgx_thread_setwait_untrusted_events_ocall,
		(void*)TestEnclave_sgx_thread_set_multiple_untrusted_events_ocall,
	}
};
sgx_status_t new_thread_func(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 0, &ocall_table_TestEnclave, NULL);
	return status;
}

sgx_status_t ecall_start_bench(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 1, &ocall_table_TestEnclave, NULL);
	return status;
}

sgx_status_t ecall_pause_bench(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 2, &ocall_table_TestEnclave, NULL);
	return status;
}

sgx_status_t ecall_stop_bench(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 3, &ocall_table_TestEnclave, NULL);
	return status;
}

sgx_status_t ecall_cleanup_bench(sgx_enclave_id_t eid)
{
	sgx_status_t status;
	status = sgx_ecall(eid, 4, &ocall_table_TestEnclave, NULL);
	return status;
}

sgx_status_t ecall_run_bench(sgx_enclave_id_t eid, int test_id, int thread_id)
{
	sgx_status_t status;
	ms_ecall_run_bench_t ms;
	ms.ms_test_id = test_id;
	ms.ms_thread_id = thread_id;
	status = sgx_ecall(eid, 5, &ocall_table_TestEnclave, &ms);
	return status;
}

sgx_status_t ecall_run_bench_with_transitions(sgx_enclave_id_t eid, int test_id, int thread_id)
{
	sgx_status_t status;
	ms_ecall_run_bench_with_transitions_t ms;
	ms.ms_test_id = test_id;
	ms.ms_thread_id = thread_id;
	status = sgx_ecall(eid, 6, &ocall_table_TestEnclave, &ms);
	return status;
}

sgx_status_t ecall_set_config(sgx_enclave_id_t eid, uint64_t** ctr, void* globalConfig)
{
	sgx_status_t status;
	ms_ecall_set_config_t ms;
	ms.ms_ctr = ctr;
	ms.ms_globalConfig = globalConfig;
	status = sgx_ecall(eid, 7, &ocall_table_TestEnclave, &ms);
	return status;
}

