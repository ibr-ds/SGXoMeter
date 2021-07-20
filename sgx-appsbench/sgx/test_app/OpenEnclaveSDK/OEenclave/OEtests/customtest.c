/*  Include section: This should only contain allowed libraries in sgx    */
#include "UtilsStructs.h"




/*  This Section can contain your helper function implementations that will be later needed to be called in the custom test function     */
static globalConfig_t *globConfPtr;





/*  These are the functions that will be called in the tool and get benchmarked. So basically, it should run your computation inside it.   */

/*
 * This is called before the benchmarking the custom_test function and can do pre processing operations
 */
void preCustomTest(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;

}

/*
 * This will be called after the benchmarking of custom_test function is finished. It can be used for cleaning up purposes
 */
void postCustomTest()
{

}

/*
 * The benchmarked function
 */
int custom_test()
{
    //printf("Write your custom code here to Benchmark\n");
    return 0;
}



