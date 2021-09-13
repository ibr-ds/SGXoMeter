#ifdef EXCEED_EPC_TEST

#include <UtilsStructs.h>

static globalConfig_t *globConfPtr;
void pre_exceed_epc_test(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;

}

void post_exceed_epc_test()
{

}

int exceed_epc_test()
{
    return 0;
}


#endif