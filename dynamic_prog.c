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

/*
 * 1713. 得到子序列的最少操作次数
 * 转换为最长公共子序列的问题：最少的操作次数，就等于target长度减去target与arr的最长公共子序列的长度
 * 动态规划解法，会超时
 * dp(i, j) -- target[0...i - 1]与arr[0...j - 1]的最长公共子序列
 * dp(i ,j):
 * i == j -- dp(i - 1, j - 1) + 1
 * i != j -- max(dp(i - 1, j), dp(i, j - 1))
 * dp(0, j) = 0, dp(i, 0) = 0
 */
int minOperations(int* target, int targetSize, int* arr, int arrSize)
{
    int dp[targetSize + 1][arrSize + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= targetSize; ++i) {
        for (int j = 1; j <= arrSize; ++j) {
            if (target[i - 1] == arr[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return targetSize - dp[targetSize][arrSize];
}