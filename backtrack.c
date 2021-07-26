/*
 * 回溯算法解题收录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "uhash/uthash.h"
#include "min_max.h"

/*
 * 131. 分割回文串
 * https://leetcode-cn.com/problems/palindrome-partitioning/
 */
#define MAX_STR_LEN 17
bool isPalindrome(char *s, int start, int end)
{
    while (end >= start) {
        if (s[end] != s[start]) {
            return false;
        }
        end--;
        start++;
    }
    return true;
}
void backtracePartition(char *s, char **tmpContainer, int *tmpConLen, char ***ret, int *returnSize, int *returnColumnSizes)
{
    if (*s == 0) {
        returnColumnSizes[*returnSize] = *tmpConLen;
        ret[*returnSize] = (char **)calloc(*tmpConLen, sizeof(char *));
        for (int i = 0; i < *tmpConLen; ++i) {
            ret[*returnSize][i] = (char *)calloc(MAX_STR_LEN, sizeof(char));
            strcpy(ret[*returnSize][i], tmpContainer[i]);
        }
        (*returnSize)++;
        return;
    }

    for (int i = 0; *(s + i) != 0; i++) {
        if (isPalindrome(s, 0, i)) {
            tmpContainer[*tmpConLen] = (char *)calloc(MAX_STR_LEN, sizeof(char));
            strncpy(tmpContainer[*tmpConLen], s, i + 1);
            (*tmpConLen)++;
            backtracePartition(s + i + 1, tmpContainer, tmpConLen, ret, returnSize, returnColumnSizes);
            free(tmpContainer[*tmpConLen - 1]);
            (*tmpConLen)--;
        }
    }
}

char ***partition(char * s, int* returnSize, int** returnColumnSizes)
{
    char ***ret = (char ***)calloc(MAX_STR_LEN * MAX_STR_LEN, sizeof(char **));
    *returnColumnSizes = (int *)calloc(MAX_STR_LEN * MAX_STR_LEN, sizeof(int));
    char **tmpContainer = (char **)calloc(MAX_STR_LEN, sizeof(char *));
    int tmpConLen = 0;

    backtracePartition(s, tmpContainer, &tmpConLen, ret, returnSize, *returnColumnSizes);

    free(tmpContainer);
    return ret;
}

/*
 * 90. 子集 II
 * https://leetcode-cn.com/problems/subsets-ii/
 * 回溯不断遍历数组，使用哈希表来存储已经求出来的子集，避免重复
 */

struct hash_node {
    int *ptr;
    UT_hash_handle hh;
};

struct hash_node *head = NULL;

void findSubsetsHelper(int *nums, int numsSize, int *returnSize, int *returnColumnSizes, int **ret, int *tmpContainer, int *containerSize)
{
    struct hash_node *s; 
    if (numsSize == 0) {
        if (*containerSize == 0) {
            //printf("got answer empty\n");
            ret[*returnSize] = (int *)calloc(1, sizeof(int));
            returnColumnSizes[*returnSize] = 0;
            (*returnSize)++;
            return;
        }

        //printf("got answer:");
        //for (int i = 0; i < *containerSize; ++i) {
        //    printf("%d ", tmpContainer[i]);
        //}
        //printf("\n");
        HASH_FIND(hh, head, tmpContainer, *containerSize, s);
        if (!s) {
            ret[*returnSize] = (int *)calloc(*containerSize, sizeof(int));
            memcpy(ret[*returnSize], tmpContainer, *containerSize * sizeof(int));
            returnColumnSizes[*returnSize] = *containerSize;
            s = (struct hash_node *)calloc(1, sizeof(struct hash_node));
            s->ptr = ret[*returnSize];
            HASH_ADD_KEYPTR(hh, head, s->ptr, *containerSize, s);
            (*returnSize)++;
        } else {
            //for (int i = 0; i < *containerSize; ++i) {
            //    printf("%d ", tmpContainer[i]);
            //}
            //printf("has been exist!\n");
        }
        return;
    }

    /* 不选择nums[0] */
    //printf("do not select %d\n", nums[0]);
    findSubsetsHelper(nums + 1, numsSize - 1, returnSize, returnColumnSizes, ret, tmpContainer, containerSize);

    /* 选择nums[0] */
    tmpContainer[*containerSize] = nums[0];
    //printf("select %d\n", nums[0]);
    (*containerSize)++;
    findSubsetsHelper(nums + 1, numsSize - 1, returnSize, returnColumnSizes, ret, tmpContainer, containerSize);
    (*containerSize)--;
}

int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    struct hash_node *p, *tmp;
    head = NULL;
    int **ret = (int **)calloc(1024, sizeof(int *));
    *returnColumnSizes = (int *)calloc(1024, sizeof(int));
    int *tmpContainer = (int *)calloc(10, sizeof(int));
    int containerSize = 0;
    *returnSize = 0;

    findSubsetsHelper(nums, numsSize, returnSize, *returnColumnSizes, ret, tmpContainer, &containerSize);

    free(tmpContainer);
    HASH_ITER(hh, head, p, tmp) {
        HASH_DEL(head, p);
        free(p);
    }
    return ret;
}

/*
 * 1743. 从相邻元素对还原数组
 * https://leetcode-cn.com/problems/restore-the-array-from-adjacent-pairs/
 * 使用回溯算法解题，超时
 * 使用图论-拓扑排序的解法，详见graph_threory.c文件
 */

static inline int numberUsed(int num, int *posUsed, int *negeUsed)
{
    return num >= 0 ? posUsed[num] : negeUsed[-num];
}

static inline void useNumber(int num, int *posUsed, int *negeUsed)
{
    if (num >= 0) {
        posUsed[num] = 1;
    } else {
        negeUsed[-num] = 1;
    }
}

static inline void unUseNumber(int num, int *posUsed, int *negeUsed)
{
    if (num >= 0) {
        posUsed[num] = 0;
    } else {
        negeUsed[-num] = 0;
    }
}

void backTrackRestoreArray(int** adjacentPairs, int adjacentPairsSize, int *ret, int* returnSize, 
    int *posUsed, int *negUsed, int *found, int firstNum)
{
    if (*found) {
        return;
    }
    if (*returnSize == adjacentPairsSize + 1) {
        *found = 1;
        return;
    }

    for (int i = 0; i < adjacentPairsSize; ++i) {
        if (firstNum == adjacentPairs[i][0] && !numberUsed(adjacentPairs[i][1], posUsed, negUsed)) {
            ret[(*returnSize)++] = adjacentPairs[i][1];
            useNumber(adjacentPairs[i][1], posUsed, negUsed);
            backTrackRestoreArray(adjacentPairs, adjacentPairsSize, ret, returnSize, posUsed, negUsed, found, adjacentPairs[i][1]);
            if (*found) {
                return;
            }
            unUseNumber(adjacentPairs[i][1], posUsed, negUsed);
            (*returnSize)--;
        }

        if (firstNum == adjacentPairs[i][1] && !numberUsed(adjacentPairs[i][0], posUsed, negUsed))
        {
            ret[(*returnSize)++] = adjacentPairs[i][0];
            useNumber(adjacentPairs[i][0], posUsed, negUsed);
            backTrackRestoreArray(adjacentPairs, adjacentPairsSize, ret, returnSize, posUsed, negUsed, found, adjacentPairs[i][0]);
            if (*found) {
                return;
            }
            unUseNumber(adjacentPairs[i][0], posUsed, negUsed);
            (*returnSize)--;            
        }
    }
}

int* restoreArray(int** adjacentPairs, int adjacentPairsSize, int* adjacentPairsColSize, int* returnSize)
{ 
    int posUsed[100001] = {0};
    int negUsed[100001] = {0};
    int found = 0;
    int *ret = (int *)calloc(adjacentPairsSize + 1, sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < adjacentPairsSize; ++i) {
        backTrackRestoreArray(adjacentPairs, adjacentPairsSize, ret, returnSize, posUsed, negUsed, &found, adjacentPairs[i][0]);
        if (found) {
            break;
        }
        backTrackRestoreArray(adjacentPairs, adjacentPairsSize, ret, returnSize, posUsed, negUsed, &found, adjacentPairs[i][1]);
        if (found) {
            break;
        }
    }

    return ret;
}