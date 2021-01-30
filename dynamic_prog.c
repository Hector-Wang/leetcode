/*
 * 动态规划题目搜录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"

/*
 * 674. 最长连续递增序列
 * https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/
 *
 * 动态规划:
 * dp(i)定义为：以i结束的最长连续递增序列, 注意连续，与最长递增序列的解法是不一样的
 * if nums[i] > nums[i - 1]
 * dp(i) = dp(i - 1) + 1
 * else
 * dp(i) = dp(i)
 *
 * base case:
 * for i in range(0, n)
 * dp(i) = i;
 */
int findLengthOfLCIS(int* nums, int numsSize)
{
    if (!nums || !numsSize) {
        return 0;
    }
    int dp[numsSize];
    for (int i = 0; i < numsSize; ++i) {
        dp[i] = 1;
    }

    for (int i = 1; i < numsSize; ++i) {
        dp[i] = nums[i] > nums[i - 1] ? dp[i - 1] + 1: dp[i];
    }

    int res = dp[0];
    for (int i = 1; i < numsSize; ++i) {
        if (res < dp[i]) {
            res = dp[i];
        }
    }
    return res;
}
