#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UtilsStructs.h"
#include "../commonTestFiles/testHeaders/argon2.h"


#define HASHLEN 32
#define PWD "password"
#define SALT "RandomSalt"



static globalConfig_t *globConfPtr;
uint8_t *pwd;
uint8_t *salt;
size_t pwdLen, saltLen;

/*  These are the functions that will be called in the tool and get benchmarked. So basically, it should run your computation inside it.   */

/*
 * This is called before the benchmarking the custom_test function and can do pre processing operations
 */
void pre_argon2_test(globalConfig_t *globalConfig)
{
    globConfPtr = globalConfig;
    pwd = (uint8_t *)strndup(PWD,8);
    pwdLen = strlen((char *)pwd);
    salt = (uint8_t *)strndup(SALT,10);
    saltLen = strlen((char *)salt);

}

/*
 * This will be called after the benchmarking of custom_test function is finished. It can be used for cleaning up purposes
 */
void post_argon2_test()
{
    free(pwd);
    free(salt);
}

/*
 * The benchmarked function
 */
int argon2_test()
{

    uint8_t hash1[HASHLEN];
    //ToDo extract these from globalConfig maybe?!
    uint32_t t_cost = 2;            // 1-pass computation
    uint32_t m_cost = (1<<16);      // 64 mebibytes memory usage
    uint32_t parallelism = 1;       // number of threads and lanes
    //return argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdLen, salt, saltLen, hash1, HASHLEN);
    return 1; //ToDo this still does not work and need to be fixed
}
