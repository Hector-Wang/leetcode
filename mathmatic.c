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
 * 三指针法。一部分是丑数数组，另一部分是权重2，3，5。下一个丑数，定义为丑数数组中的数乘以权重，所得的最小值。
 * 那么，2该乘以谁？3该乘以谁？5该乘以谁？
 * 其一，使用三个指针idx[3]，告诉它们。比如，2应该乘以ugly[idx[0]]，即数组中的第idx[0]个值。(权重2，3，5分别对应指针，idx[0],idx[1],idx[2])
 * 其二，当命中下一个丑数时，说明该指针指向的丑数 乘以对应权重所得积最小。此时，指针应该指向下一个丑数。(idx[]中保存的是丑数要乘的权重)
 * 其三，要使用三个并列的if让指针指向一个更大的数，不能用if-else。因为有这种情况：
 * 丑数6，可能由于丑数2乘以权重3产生；也可能由于丑数3乘以权重2产生。
 * 丑数10，... 等等。
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

/*
 * 154. 寻找旋转排序数组中的最小值 II
 * https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/
 */
int findMin(int* nums, int numsSize)
{
    int ret = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[i - 1]) {
            return nums[i];
        }
    }
    return ret;
}

/*
 * 153. 寻找旋转排序数组中的最小值
 * https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/
 */
int findMinI(int* nums, int numsSize)
{
    int ret = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[i - 1]) {
            return nums[i];
        }
    }
    return ret;
}