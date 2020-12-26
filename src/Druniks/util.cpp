#include <iostream>
#include "util.h"

bool isBigEndian()
{
    union {
        uint32_t i;
        char c[4];
    } bint = { 0x01020304 };

    return bint.c[0] == 1;
}

bool isLittleEndian()
{
    return !isBigEndian();
}