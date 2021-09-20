#ifdef EXCEED_EPC_TEST_SEQ

#include <UtilsStructs.h>

static globalConfig_t *globConfPtr;
char *sequentialAccessBuffer;
char temp;

void pre_exceed_epc_test_seq(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    size_t readStrSize = globConfPtr->READ_BUFLEN * sizeof(char);
    sequentialAccessBuffer = (char *) malloc(readStrSize + 1);
    for(int i = 0; i < globConfPtr->READ_BUFLEN; i++)
    {
        sequentialAccessBuffer[i] = 'a';
    }
    sequentialAccessBuffer[readStrSize] = '\0';

}

void post_exceed_epc_test_seq()
{
    free(sequentialAccessBuffer);
}

int exceed_epc_test_seq()
{
    for(int i = 0; i < globConfPtr->READ_BUFLEN; i++)
    {
        temp = sequentialAccessBuffer[i];
    }
    return 0;
}


#endif