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

    return 0;
}

