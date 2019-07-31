//
// Created by moe on 17.07.19.
//

#include "BenchThread.h"


/*
 * Local variables referring global variables, which their values are changed from multiple threads
 */
static volatile int do_bench = 0;
volatile uint64_t *bench_counter = 0;
static globalConfig_t *GLOBAL_CONFIG;


struct evp_pkey_st {
    int type;
    int save_type;
    int references;
    const EVP_PKEY_ASN1_METHOD *ameth;
    ENGINE *engine;
    union {
        char *ptr;
# ifndef OPENSSL_NO_RSA
        struct rsa_st *rsa;     /* RSA */
# endif
# ifndef OPENSSL_NO_DSA
        struct dsa_st *dsa;     /* DSA */
# endif
# ifndef OPENSSL_NO_DH
        struct dh_st *dh;       /* DH */
# endif
# ifndef OPENSSL_NO_EC
        struct ec_key_st *ec;   /* ECC */
# endif
    } pkey;
    int save_parameters;
    STACK_OF(X509_ATTRIBUTE) *attributes; /* [ 0 ] */
    CRYPTO_RWLOCK *lock;
} /* EVP_PKEY */ ;

#ifdef RSA_KEY_GEN
int rsa_key_gen()
{
	BIGNUM *bn = BN_new();
	if (bn == NULL) {
		printf("BN_new failure: %ld\n", ERR_get_error());
	    return 1;
	}
	int ret = BN_set_word(bn, RSA_F4);
    if (!ret) {
       	printf("BN_set_word failure\n");
	    return 1;
	}

	RSA *keypair = RSA_new();
	if (keypair == NULL) {
		printf("RSA_new failure: %ld\n", ERR_get_error());
	    return 1;
	}
	ret = RSA_generate_key_ex(keypair, GLOBAL_CONFIG->RSA_BITS, bn, NULL);
	if (!ret) {
        printf("RSA_generate_key_ex failure: %ld\n", ERR_get_error());
	    return 1;
	}

	EVP_PKEY *evp_pkey = EVP_PKEY_new();
	if (evp_pkey == NULL) {
		printf("EVP_PKEY_new failure: %ld\n", ERR_get_error());
		return 1;
	}
	EVP_PKEY_assign_RSA(evp_pkey, keypair);

	// public key - string
	int len = i2d_PublicKey(evp_pkey, NULL);
	unsigned char *buf = (unsigned char *) malloc (len + 1);
	unsigned char *tbuf = buf;
	i2d_PublicKey(evp_pkey, &tbuf);

#ifdef PRINT_CHECKS
	// print public key
	printf ("{\"public\":\"");
	int i;
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	// private key - string
	len = i2d_PrivateKey(evp_pkey, NULL);
	buf = (unsigned char *) malloc (len + 1);
	tbuf = buf;
	i2d_PrivateKey(evp_pkey, &tbuf);


#ifdef PRINT_CHECKS
    // print private key
	printf ("{\"private\":\"");
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	BN_free(bn);

	EVP_PKEY_free(evp_pkey);

	if (evp_pkey->pkey.ptr != NULL) {
	  RSA_free(keypair);
	}
	return 0;
}
#endif //RSA KEY GEN

#define ADD_ENTROPY_SIZE	32

#ifdef ELLIPTIC_CURVE_KEY_GEN
int ec_key_gen()
{
	unsigned char entropy_buf[ADD_ENTROPY_SIZE] = {0};

	RAND_add(entropy_buf, sizeof(entropy_buf), ADD_ENTROPY_SIZE);
	RAND_seed(entropy_buf, sizeof(entropy_buf));

	EC_KEY * ec = NULL;
    int eccgroup;
    eccgroup = OBJ_txt2nid("secp384r1");
    ec = EC_KEY_new_by_curve_name(eccgroup);
    if (ec == NULL) {
    	printf("EC_KEY_new_by_curve_name failure: %ld\n", ERR_get_error());
	    return 1;
    }

	EC_KEY_set_asn1_flag(ec, OPENSSL_EC_NAMED_CURVE);

	int ret = EC_KEY_generate_key(ec);
	if (!ret) {
        printf("EC_KEY_generate_key failure\n");
	    return 1;
	}

	EVP_PKEY *ec_pkey = EVP_PKEY_new();
	if (ec_pkey == NULL) {
		printf("EVP_PKEY_new failure: %ld\n", ERR_get_error());
		return 1;
	}
	EVP_PKEY_assign_EC_KEY(ec_pkey, ec);

	// public key - string
	int len = i2d_PublicKey(ec_pkey, NULL);
	unsigned char *buf = (unsigned char *) malloc (len + 1);
	unsigned char *tbuf = buf;
	i2d_PublicKey(ec_pkey, &tbuf);


#ifdef PRINT_CHECKS
    // print public key
	printf ("{\"public\":\"");
	int i;
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	// private key - string
	len = i2d_PrivateKey(ec_pkey, NULL);
	buf = (unsigned char *) malloc (len + 1);
	tbuf = buf;
	i2d_PrivateKey(ec_pkey, &tbuf);

#ifdef PRINT_CHECKS
	// print private key
	printf ("{\"private\":\"");
	for (i = 0; i < len; i++) {
	    printf("%02x", (unsigned char) buf[i]);
	}
	printf("\"}\n");
#endif
	free(buf);

	EVP_PKEY_free(ec_pkey);
	if (ec_pkey->pkey.ptr != NULL) {
	  EC_KEY_free(ec);
	}
	return 0;
}
#endif  //ELLIPTIC CURVE KEY GEN


/**
 * This includes the generation of the test function wrappers
 */
#include "testFunctionsGeneration.h"

/**
 * This includes a common array of test names
 */
#include "testNames.h"

/*
 * This includes a function pointer array of all chosen modules
 */
#include "testFunctionPointerArray.h"


/*
 * The 3 Benchmark status
 */
#define PAUSED    0
#define RUNNING   1
#define STOPED    2

void start_bench(void)
{
    do_bench = RUNNING;
}

void stop_bench(void)
{
    do_bench = STOPED;
}

void pause_bench(void)
{
    do_bench = PAUSED;
}

void set_config(uint64_t *ctr, void *globalConfig)
{
    bench_counter = ctr;
    if(globalConfig != NULL)
    {
        GLOBAL_CONFIG = (globalConfig_t *)globalConfig;
    }
    // OPENSSL_init_crypto(0, NULL);

    /*
     * This includes all available pre function calls of the chosen modules
     */
    #include "preTestFunctionCalls.h"
}

void run_bench(int test_id)
{

    while(do_bench == PAUSED)
    { __asm__("pause");}

    int iterCounter = 0;

#ifdef PRINT_CHECKS
    printf("Start tests\n");
#endif

    while(do_bench == RUNNING)
    {
        (*testFuncPtr[test_id])();
        *bench_counter += 1;

        if(GLOBAL_CONFIG->NUM_OF_ITERATION > 0) {
            iterCounter++;
            //check the counter either against the given one with a query or the one set globally
            if(iterCounter == GLOBAL_CONFIG->NUM_OF_ITERATION)      break;
        }
    }

    /*
     * This includes the available post function calls of the chosen modules
     */
    #include "postTestFunctionCalls.h"
}
