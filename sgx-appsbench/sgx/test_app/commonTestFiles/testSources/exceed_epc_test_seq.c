#ifdef EXCEED_EPC_TEST_SEQ

#include <UtilsStructs.h>

static globalConfig_t *globConfPtr;
char *randomAccessBuffer;
char temp;

void pre_exceed_epc_test_seq(globalConfig_t *globalConfig)
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

void post_exceed_epc_test_seq()
{
    free(randomAccessBuffer);
}

int exceed_epc_test_seq()
{
    for(int i = 0; i < globConfPtr->READ_BUFLEN; i++)
    {
        temp = randomAccessBuffer[i];
    }
    return 0;
}


#endif