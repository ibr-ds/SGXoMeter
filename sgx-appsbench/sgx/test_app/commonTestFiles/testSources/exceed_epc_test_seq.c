#ifdef EXCEED_EPC_TEST_SEQ

#include <UtilsStructs.h>

static globalConfig_t *globConfPtr;
void pre_exceed_epc_test_seq(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;

}

void post_exceed_epc_test_seq()
{

}

int exceed_epc_test_seq()
{
    return 0;
}


#endif