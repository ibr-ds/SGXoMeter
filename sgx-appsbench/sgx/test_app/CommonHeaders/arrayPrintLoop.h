//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_ARRAYPRINTLOOP_H
#define SGX_APPSBENCH_ARRAYPRINTLOOP_H

// print array either to an output file or to the console
for (int i = 0; i < NUM_OF_TEST_MODULES; ++i)
{
    float warmRate    = (float)array[i].warmCnt / (float)GLOBAL_CONFIG.WARMUP_TIME;
    float runtimeRate = (float)array[i].runCnt  / (float)GLOBAL_CONFIG.RUNTIME;
    #ifdef WRITE_LOG_FILE

    if(strcmp(test_names[i + DUMMY_INDEX], "custom SHA256 test") == 0)
    {
    #ifdef CUSTOM_SHA256_TEST
    fprintf(fp,"%s,%lu,%lu,%.5f,%lu,%.5f\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.HASH256_LEN ,array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate);
    #endif //CUSTOM_SHA256_TEST
    } else if(strcmp(test_names[i + DUMMY_INDEX], "rsa key gen") == 0)
    {
    #ifdef RSA_KEY_GEN
    fprintf(fp,"%s,%d,%lu,%.5f,%lu,%.5f\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.RSA_BITS, array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate);
    #endif // RSA_KEY_GEN
    } else if(strcmp(test_names[i + DUMMY_INDEX], "DNA matching") == 0)
    {
    #ifdef DNA_PATTERN_MATCHING
    fprintf(fp,"%s,%lu,%lu,%.5f,%lu,%.5f\n", test_names[i + DUMMY_INDEX], strlen(GLOBAL_CONFIG.DNA_INPUT), array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate);
    #endif //DNA_PATTERN_MATCHING
    } else if(strcmp(test_names[i + DUMMY_INDEX], "rsa crypto test") == 0 || strcmp(test_names[i + DUMMY_INDEX], "rsa signing test") == 0)
    {
    #if defined(RSA_CRYPTO_TEST) || defined(RSA_SIGN_TEST)
    fprintf(fp,"%s,%d,%lu,%lu,%.5f,%lu,%.5f\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.RSA_BITS, GLOBAL_CONFIG.RSA_MESSAGE_LEN, array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate);
    #endif //RSA_CRYPTO_TEST || RSA_SIGN_TEST
    } else {
    fprintf(fp,"%s,%lu,%.5f,%lu,%.5f\n", test_names[i + DUMMY_INDEX], array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate);
    }
    #else
    printf("%s,%lu,%.5f,%lu,%.5f\n", test_names[i + DUMMY_INDEX], array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate);
#endif //WRITE_LOG_FILE
}

#endif //SGX_APPSBENCH_ARRAYPRINTLOOP_H
