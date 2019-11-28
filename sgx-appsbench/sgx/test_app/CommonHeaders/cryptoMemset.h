//
// Created by moe on 28.11.19.
//

#ifndef SGX_APPSBENCH_CRYPTOMEMSET_H
#define SGX_APPSBENCH_CRYPTOMEMSET_H

void* memset_s(void* dest, size_t destsz, int c, size_t len) {
    return memset(dest, c, destsz < len ? destsz : len);
}

int consttime_memequal(const void *b1, const void *b2, size_t len)
{
    const unsigned char *c1 = b1, *c2 = b2;
    unsigned int res = 0;

    while (len--)
        res |= *c1++ ^ *c2++;

    /*
     * Map 0 to 1 and [1, 256) to 0 using only constant-time
     * arithmetic.
     *
     * This is not simply `!res' because although many CPUs support
     * branchless conditional moves and many compilers will take
     * advantage of them, certain compilers generate branches on
     * certain CPUs for `!res'.
     */
    return (1 & ((res - 1) >> 8));
}

#endif //SGX_APPSBENCH_CRYPTOMEMSET_H
