#ifdef EXCEED_EPC_TEST_RAND

#include <UtilsStructs.h>

static globalConfig_t *globConfPtr;
char *randomAccessBuffer;
char temp;

void pre_exceed_epc_test_rand(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    size_t readStrSize = globConfPtr->READ_BUFLEN * sizeof(char);
    randomAccessBuffer = (char *) malloc(readStrSize + 1);
    for(int i = 0; i < globConfPtr->READ_BUFLEN; i++)
    {
        randomAccessBuffer[i] = 'a';
    }
    randomAccessBuffer[readStrSize] = '\0';


}

void post_exceed_epc_test_rand()
{
    free(randomAccessBuffer);
}

int exceed_epc_test_rand()
{
    for(int i = 0; i < globConfPtr->READ_BUFLEN; i++)
    {
        temp = randomAccessBuffer[globConfPtr->READ_ACCESS_LIST[i]];
    }
    return 0;
}


#endif