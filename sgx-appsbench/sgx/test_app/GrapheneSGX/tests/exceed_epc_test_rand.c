#ifdef EXCEED_EPC_TEST_RAND

#include <UtilsStructs.h>

static globalConfig_t *globConfPtr;
void pre_exceed_epc_test_rand(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    int randomAccessArray[globConfPtr->READ_BUFLEN];
    for(int i = 0; i < globConfPtr->READ_BUFLEN; i++)
    {
        randomAccessArray[i] = i;
    }

}
void post_exceed_epc_test_rand()
{

}

int exceed_epc_test_rand()
{
    return 0;
}


#endif