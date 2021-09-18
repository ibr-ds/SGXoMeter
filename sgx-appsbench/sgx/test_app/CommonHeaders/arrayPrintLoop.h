//
// Created by moe on 29.07.19.
//

#ifndef SGX_APPSBENCH_ARRAYPRINTLOOP_H
#define SGX_APPSBENCH_ARRAYPRINTLOOP_H

#ifdef WRITE_LOG_FILE
#define printOut(msg...) fprintf(fp,msg)
#else
#define printOut(msg...) printf(msg)
#endif



// print array either to an output file or to the console
for (int i = 0; i < NUM_OF_TEST_MODULES; ++i)
{
    float warmRate    = (float)array[i].warmCnt / (float)GLOBAL_CONFIG.WARMUP_TIME;
    float runtimeRate = (float)array[i].runCnt  / (float)array[i].totalRuntime;

    if(strcmp(test_names[i + DUMMY_INDEX], "custom SHA256 test") == 0)
    {
        #ifdef CUSTOM_SHA256_TEST
        printOut("%s,%lu,%lu,%.5f,%lu,%.5f,%lu\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.HASH256_LEN,
                array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate, array[i].totalRuntime);
        #endif //CUSTOM_SHA256_TEST
    } else if(strcmp(test_names[i + DUMMY_INDEX], "rsa key gen") == 0)
    {
        #ifdef RSA_KEY_GEN
        printOut("%s,%d,%lu,%.5f,%lu,%.5f,%lu\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.RSA_BITS, array[i].warmCnt,
                warmRate, array[i].runCnt, runtimeRate, array[i].totalRuntime);
        #endif // RSA_KEY_GEN
    } else if(strcmp(test_names[i + DUMMY_INDEX], "DNA matching") == 0)
    {
        #ifdef DNA_PATTERN_MATCHING
        printOut("%s,%lu,%lu,%.5f,%lu,%.5f,%lu\n", test_names[i + DUMMY_INDEX], strlen(GLOBAL_CONFIG.DNA_INPUT),
                array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate, array[i].totalRuntime);
        #endif //DNA_PATTERN_MATCHING
    } else if(strcmp(test_names[i + DUMMY_INDEX], "rsa crypto test") == 0 || strcmp(test_names[i + DUMMY_INDEX], "rsa signing test") == 0)
    {
        #if defined(RSA_CRYPTO_TEST) || defined(RSA_SIGN_TEST)
        printOut("%s,%d,%lu,%lu,%.5f,%lu,%.5f,%lu\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.RSA_BITS,
                GLOBAL_CONFIG.RSA_MESSAGE_LEN, array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate, array[i].totalRuntime);
    #endif //RSA_CRYPTO_TEST || RSA_SIGN_TEST
    } else if(strcmp(test_names[i + DUMMY_INDEX], "sgx encrypto test")     == 0
           || strcmp(test_names[i + DUMMY_INDEX], "sgx decrypto test")     == 0
           || strcmp(test_names[i + DUMMY_INDEX], "sgx decrypto ext test") == 0
           || strcmp(test_names[i + DUMMY_INDEX], "sgx decrypto encrypto test") == 0
           || strcmp(test_names[i + DUMMY_INDEX], "AEAD AES256GCM ENCRYPT TEST") == 0
           || strcmp(test_names[i + DUMMY_INDEX], "AEAD AES256GCM DECRYPT TEST") == 0)
    {
        #if defined(SGX_ENCRYPTO_TEST) || defined(SGX_DECRYPTO_TEST) || defined(SGX_DECRYPTO_EXT_TEST) || defined(SGX_DECRYPTO_ENCRYPTO) || defined(AEAD_AES256GCM_DECRYPT_TEST) || defined(AEAD_AES256GCM_ENCRYPT_TEST)
        printOut("%s,%lu,%lu,%.5f,%lu,%.5f,%lu\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.CRYPTO_BUFLEN,
                array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate, array[i].totalRuntime);
        #endif //SGX SDK EN/DECRYPTO
    } else if(strcmp(test_names[i + DUMMY_INDEX], "EXCEED EPC TEST RAND") == 0
           || strcmp(test_names[i + DUMMY_INDEX], "EXCEED EPC TEST SEQ") == 0)
    {
        #if defined(EXCEED_EPC_TEST_RAND) || defined(EXCEED_EPC_TEST_SEQ)
        printOut("%s,%lu,%lu,%.5f,%lu,%.5f,%lu\n", test_names[i + DUMMY_INDEX], GLOBAL_CONFIG.READ_BUFLEN,
                array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate, array[i].totalRuntime);
        #endif
    } else {
        printOut("%s,%lu,%.5f,%lu,%.5f,%lu\n", test_names[i + DUMMY_INDEX], array[i].warmCnt, warmRate, array[i].runCnt, runtimeRate, array[i].totalRuntime);
    }
}

#endif //SGX_APPSBENCH_ARRAYPRINTLOOP_H
