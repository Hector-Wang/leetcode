/*
 * 滑动窗口类题目收录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"

/*
 * 1208. 尽可能使字符串相等
 * https://leetcode-cn.com/problems/get-equal-substrings-within-budget/
 * 先计算出每个字符转换的开销，组成一个数组，然后在这个数组里面进行滑动，取得和小于
 * 等于最大预算的最大长度即可
 */

int equalSubstring(char * s, char * t, int maxCost)
{
    int len = strlen(s);
    int costs[len];
    int res = 0;
    int left, right = 0;
    
    for (int i = 0; i < len; ++i) {
        costs[i] = abs(s[i] - t[i]);
    }

    int curCostSum = 0;
    while (right < len) {
        curCostSum += costs[right++];
        if (curCostSum <= maxCost) {
            res = max(res, right - left);
        } else {
            while (curCostSum > maxCost) {
                curCostSum -= costs[left];
                left++;
            }
        }
    }
    return res;
}


/*
 * 697. 数组的度
 * https://leetcode-cn.com/problems/degree-of-an-array/
 */

int findShortestSubArray(int* nums, int numsSize)
{
    int degree[50000] = {0};
    int maxDegree = 0;
    int res = numsSize;
    for (int i = 0; i < numsSize; ++i) {
        degree[nums[i]]++;
        maxDegree = max(maxDegree, degree[nums[i]]);
    }

    memset(degree, 0, sizeof(degree));

    int left = 0, right = 0;
    int curMax = 0;
    while (right < numsSize) {
        degree[nums[right]]++;
        curMax = max(curMax, degree[nums[right]]);
        right++;
        while (curMax == maxDegree) {
            res = min(res, right - left);
            if (curMax == degree[nums[left]]) {
                curMax--;
            }
            degree[nums[left]]--;
            left++;
        }
    }

    return res;
}


/*
 * 1052. 爱生气的书店老板
 * https://leetcode-cn.com/problems/grumpy-bookstore-owner/
 */
int maxSatisfied(int *customers, int customersSize, int *grumpy, int grumpySize, int X)
{
    int res = 0;

    int maxSatisfiedNum = 0;
    for (int i = 0 ; i < customersSize; ++i) {
        if (!grumpy[i]) {
            maxSatisfiedNum += customers[i];
        }
    }

    for (int i = 0; i < X && i < customersSize; ++i) {
        if (grumpy[i]) {
            maxSatisfiedNum += customers[i];
        }
    }

    res = maxSatisfiedNum;

    for (int i = 1; i < customersSize - X + 1; ++i) {
        if (grumpy[i - 1]) {
            maxSatisfiedNum -= customers[i - 1];
        }
        if (grumpy[i + X - 1]) {
            maxSatisfiedNum += customers[i + X - 1];
        }
        res = max(maxSatisfiedNum, res);
    }

    return res;
}