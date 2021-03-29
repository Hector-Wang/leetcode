/*
 * 数字类题目收录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"


/*
 * 190. 颠倒二进制位
 * https://leetcode-cn.com/problems/reverse-bits/
 */
uint32_t reverseBits(uint32_t n) 
{
    uint32_t ret = 0;
    for (int i = 0; i < 32; ++i) {
        uint32_t bit = (n & 0x80000000u) >> 31;
        n <<= 1;
        ret |= (bit << i);
    }
    return ret;
}
