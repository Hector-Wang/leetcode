#ifndef C_DEMO_H
#define C_DEMO_H

int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize);

int regionsBySlashes(char ** grid, int gridSize);

int maxNumEdgesToRemove(int n, int** edges, int edgesSize, int* edgesColSize);

int* addToArrayForm(int* A, int ASize, int K, int* returnSize);

int numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize);

int pivotIndex(int* nums, int numsSize);

int findLengthOfLCIS(int* nums, int numsSize);

int numSimilarGroups(char ** strs, int strsSize);

int minimumEffortPath(int **heights, int heightsSize, int *heightsColSize);

int* getRow(int rowIndex, int* returnSize);

int findShortestSubArray(int* nums, int numsSize);

int maxSatisfied(int *customers, int customersSize, int *grumpy, int grumpySize, int X);

char ***partition(char * s, int* returnSize, int** returnColumnSizes);

#endif