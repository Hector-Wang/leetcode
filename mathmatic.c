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

/*
 * 263. 丑数
 * https://leetcode-cn.com/problems/ugly-number/
 */
bool isUgly(int n)
{
    if (n <= 0) {
        return false;
    }
    while (n % 5 == 0) {
        n /= 5;
    }
    while (n % 3 == 0) {
        n /= 3;
    }
    while (n % 2 == 0) {
        n /= 2;
    }

    return n == 1;
}

/*
 * 264. 丑数 II
 * https://leetcode-cn.com/problems/ugly-number-ii/
 */
int nthUglyNumber(int n)
{
    int ugly[n];
    int index[3] = {0};

    for (int i = 0; i < n; ++i) {
        ugly[i] = 1;
    }

    for (int i = 1; i < n; ++i) {
        int a = ugly[index[0]] * 2;
        int b = ugly[index[1]] * 3;
        int c = ugly[index[2]] * 5;

        int next = max(a, b);
        next = max(next, c);

        if (next == a) {
            index[0]++;
        }
        if (next == b) {
            index[1]++;
        }
        if (next == c) {
            index[2]++;
        }
        ugly[i] = next;
    }
    return ugly[n - 1];
}
