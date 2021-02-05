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
