#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"

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

int main(int argc, const char *argv[])
{
    int n = 4;
    int connection1[] = {0, 1};
    int connection2[] = {0, 2};
    int connection3[] = {1, 2};
    int *connectionsPtr[] = {connection1, connection2, connection3};
    int connectionsColSize[] = {2, 2, 2};
    int connectionsSize = 3;

    int res = makeConnected(n, connectionsPtr, connectionsSize, connectionsColSize);

    printf("%s %d\n", "hello world --- ", res);
    return 0;
}

