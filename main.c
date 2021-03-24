/*
 * main文件，用于编译调试
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "main.h"

int printArray(int *array, int arraySize)
{
    printf("res =");
    for (int i = 0; i < arraySize; ++i) {
        printf(" %d", array[i]);
    }
    printf("\n");
}

int main(int argc, const char *argv[])
{
    /*******************************************************************************/
    int n = 4;
    int connection1[] = {0, 1};
    int connection2[] = {0, 2};
    int connection3[] = {1, 2};
    int *connectionsPtr[] = {connection1, connection2, connection3};
    int connectionsColSize[] = {2, 2, 2};
    int connectionsSize = 3;

    int res = makeConnected(n, connectionsPtr, connectionsSize, connectionsColSize);
    printf("%s %d\n", "hello world --- ", res);
    /*******************************************************************************/
    int A[] = {1,2,0,0};
    int K = 34;
    int returnSize1;
    int *ret1 = addToArrayForm(A, 4, 34, &returnSize1);
    printArray(ret1, returnSize1);
    free(ret1);
    /*******************************************************************************/
    char *S = "\\/";
    printf("%s %d %c\n", S, (int)strlen(S), S[1]);
    /*******************************************************************************/
    int nums[] = {0,0,0,0,1};
    int ret2 = pivotIndex(nums, 5);
    printf("ret2 = %d\n", ret2);
    /*******************************************************************************/
    char *strs[] = {"tars","rats","arts","star"};
    int ret3 = numSimilarGroups(strs, 4);
    printf("ret3 = %d\n", ret3);
    /*******************************************************************************/
    int returnSize4;
    int *ret4 = getRow(1, &returnSize4);
    printArray(ret4, returnSize4);
    free(ret4);
    /*******************************************************************************/
    int nums5[] = {1,2,2,3,1,4,2};
    int ret5 = findShortestSubArray(nums5, 7);
    printf("ret5 = %d\n", ret5);
    /*******************************************************************************/
    char s[17] = "aabcbcc";
    int returnSize6;
    int *returnColumnSizes6;
    char ***ret6 = partition(s, &returnSize6, &returnColumnSizes6);
    printf("retSize = %d\n", returnSize6);
    printf("retColSizes: ");
    for (int i = 0; i < returnSize6; ++i) {
        printf("%d ", returnColumnSizes6[i]);
    }
    printf("\n---------------------------------\n");
    for (int i = 0; i < returnSize6; ++i) {
        for (int j = 0; j < returnColumnSizes6[i]; ++j) {
            printf("%s ", ret6[i][j]);
            free(ret6[i][j]);
        }
        printf("\n");
        free(ret6[i]);
    }
    printf("---------------------------------\n");
    free(ret6);
    free(returnColumnSizes6);
    
    return 0;
}

