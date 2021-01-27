#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"

static int max(int a, int b)
{
    return a > b ? a : b;
}

static int min(int a, int b)
{
    return a < b ? a : b;
}

/* leetcode 1319. 连通网络的操作次数 并查集
   https://leetcode-cn.com/problems/number-of-operations-to-make-network-connected/
   问题思路转换一下：统计当前网络中所有并查集的个数
   联通m个并查集需要变动的线的个数为m-1
   联通n个计算机需要最小的线的个数为n-1，如果线缆数量小于n-1，那么需要返回-1
*/

int find(int x, int *parent)
{
    if (x != parent[x]) {
        parent[x] = find(parent[x], parent);
    }
    return parent[x];
}

void merge(int x, int y, int *parent)
{
    parent[y] = x;
}

void initParent(int *parent, int len)
{
    for (int i = 0; i < len; ++i) {
        parent[i] = i;
    }
}

int makeConnected(int n, int** connections, int connectionsSize, int* connectionsColSize)
{
    int parent[n];
    int numOfSet = 0;

    initParent(parent, n);

    for (int i = 0; i < connectionsSize; ++i) {
        int x = connections[i][0];
        int y = connections[i][1];
        int px = find(x, parent);
        int py = find(y, parent);
        if (px != py) {
            merge(px, py, parent);
        }
    }

    for (int i = 0; i < n; ++i) {
        if (i == find(i, parent)) {
            numOfSet++;
        }
    }

    if (connectionsSize < n - 1) {
        return -1;
    } else {
        return numOfSet - 1;
    }
}


/*
674. 最长连续递增序列
https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/

动态规划:
dp(i)定义为：以i结束的最长连续递增序列, 注意连续，与最长递增序列的解法是不一样的
if nums[i] > nums[i - 1]
dp(i) = dp(i - 1) + 1
else
dp(i) = dp(i)

base case:
for i in range(0, n)
dp(i) = i;
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
989. 数组形式的整数加法
https://leetcode-cn.com/problems/add-to-array-form-of-integer/

*/

int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
    int KSize = 0;
    int tmpK = K;
    while (tmpK > 0) {
        KSize++;
        tmpK /= 10;
    }

    int retLen = max(ASize, KSize) + 1;
    int *ret = (int *)calloc(retLen, sizeof(int));
    *returnSize = retLen;
    int AIndex = ASize - 1;
    int carry = 0;

    for (int i = retLen - 1; i >= 0; --i) {
        int a = AIndex >= 0 ? A[AIndex--] : 0;
        int k = K > 0 ? K % 10 : 0;
        K /= 10;
        ret[i] = (a + k + carry) % 10;
        carry = (a + k + carry) / 10;
    }

    if (ret[0] == 0) {
        (*returnSize)--;
        memmove(ret, ret + 1, (*returnSize) * sizeof(int));
    }
    return ret;
}

/*
leetcode 959. 由斜杠划分区域
https://leetcode-cn.com/problems/regions-cut-by-slashes/
并查集
*/

void mergeRegions(char ** grid, int gridSize, int *parent)
{
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            int baseId = (i * gridSize + j) * 4;
            switch (grid[i][j]) {
                int pa, pb, pc, pd;
                case ' ':
                    pa = find(baseId, parent);
                    pb = find(baseId + 1, parent);
                    pc = find(baseId + 2, parent);
                    pd = find(baseId + 3, parent);
                    merge(pa, pb, parent);
                    merge(pa, pc, parent);
                    merge(pa, pd, parent);
                break;
                case '/':
                    pa = find(baseId + 3, parent);
                    pb = find(baseId + 2, parent);
                    merge(pa, pb, parent);
                    pc = find(baseId + 1, parent);
                    pd = find(baseId, parent);
                    merge(pc, pd, parent);   
                break;
                case '\\':
                    pa = find(baseId + 3, parent);
                    pb = find(baseId, parent);
                    merge(pa, pb, parent);
                    pc = find(baseId + 2, parent);
                    pd = find(baseId + 1, parent);
                    merge(pc, pd, parent); 
                break;
                default:
                break;
            }
            if (j > 0) {
                int leftBaseId = (i * gridSize + j - 1) * 4;
                int pa = find(leftBaseId + 3, parent);
                int pb = find(baseId + 1, parent);
                if (pa != pb) {
                    merge(pa, pb, parent);
                }
            }
            if (i > 0) {
                int upBaseId = ((i - 1) * gridSize + j) * 4;
                int pa = find(upBaseId + 2, parent);
                int pb = find(baseId, parent);
                if (pa != pb) {
                    merge(pa, pb, parent);
                }
            }
        }
    }
}

int regionsBySlashes(char ** grid, int gridSize)
{
    int totalNodeNum = 4 * gridSize * gridSize;
    int parent[totalNodeNum];

    for (int i = 0; i < totalNodeNum; ++i) {
        parent[i] = i;
    }

    mergeRegions(grid, gridSize, parent);

    int res = 0;
    for (int i = 0; i < totalNodeNum; ++i) {
        if (i == find(i, parent)) {
            res++;
        }
    }
    
    return res;
}

/*
1128. 等价多米诺骨牌对的数量
https://leetcode-cn.com/problems/number-of-equivalent-domino-pairs/
*/

/* 暴力解法，超出时间限制

bool equal(int *dominoeA, int *dominoeB)
{
    return (dominoeA[0] == dominoeB[0] && dominoeA[1] == dominoeB[1]) ||
           (dominoeA[0] == dominoeB[1] && dominoeA[1] == dominoeB[0]);
}

int numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize)
{
    int res = 0;
    for (int i = 0; i < dominoesSize; ++i) {
        for (int j = i + 1; j < dominoesSize; ++j) {
            if (equal(dominoes[i], dominoes[j])) {
                res++;
            }
        }
    }
    return res;
}
*/

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int combine(int m, int n)
{
	int ans = 1;
	if(m < n - m){
        m = n-m;
    }
	for(int i = m + 1; i <= n; i++) {
        ans *= i;
    }
	for(int j = 1; j <= n - m; j++) {
        ans /= j;
    }
	return ans;
}

int numEquivDominoPairs(int** dominoes, int dominoesSize, int* dominoesColSize)
{
    int num[100] = {0};
    for (int i = 0; i < dominoesSize; ++i) {
        if (dominoes[i][0] > dominoes[i][1]) {
            swap(&dominoes[i][0], &dominoes[i][1]);
        }
    }

    for (int i = 0; i < dominoesSize; ++i) {
        num[dominoes[i][0] * 10 + dominoes[i][1]]++;
    }

    int res = 0;
    for (int i = 0; i < 100; ++i) {
        if (num[i] > 1) {
            res += combine(2, num[i]);
        }
    }
    return res;
}


/*
1579. 保证图可完全遍历
https://leetcode-cn.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/
*/

void tryToRemoveEdge(int** edges, int edgesSize, int *parent, int type, int *res)
{
    for (int i = 0; i < edgesSize; ++i) {
        if (edges[i][0] == type) {
            int pa = find(edges[i][1], parent);
            int pb = find(edges[i][2], parent);
            if (pa != pb) {
                merge(pa, pb, parent);
            } else {
                (*res)++;
            }
        }
    }    
}

bool isAllConnected(int *parent, int n)
{
    int setNum = 0;
    for (int i = 1; i <= n; ++i) {
        if (i == find(i, parent)) {
            setNum++;
        }
    }
    return setNum == 1;
}

int maxNumEdgesToRemove(int n, int** edges, int edgesSize, int* edgesColSize)
{
    int parentComm[n + 1];
    int parentAlice[n + 1];
    int parentBob[n + 1];
    int res = 0;

    initParent(parentComm, n + 1);
    tryToRemoveEdge(edges, edgesSize, parentComm, 3, &res);
    
    memcpy(parentAlice, parentComm, sizeof(parentComm));
    memcpy(parentBob, parentComm, sizeof(parentComm));

    tryToRemoveEdge(edges, edgesSize, parentAlice, 1, &res);
    tryToRemoveEdge(edges, edgesSize, parentBob, 2, &res);
    
    if (isAllConnected(parentAlice, n) && isAllConnected(parentBob, n)) {
        return res;
    } else {
        return -1;
    }
}

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
    /*******************************************************************************/

    char *S = "\\/";
    printf("%s %d %c\n", S, (int)strlen(S), S[1]);

    return 0;
}

