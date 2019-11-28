//
// Created by moe on 28.11.19.
//

#ifndef SGX_APPSBENCH_OCALLDEFINITIONS_H
#define SGX_APPSBENCH_OCALLDEFINITIONS_H

void* ocallMalloc(size_t size)
{
    return malloc(size);
}

void ocallFree(void * buffer)
{
    free(buffer);
}

#endif //SGX_APPSBENCH_OCALLDEFINITIONS_H
