/*
 * 回溯算法解题收录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
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