/*
 * 并查集题目搜录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"

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

/* 
 * leetcode 1319. 连通网络的操作次数 并查集
 * https://leetcode-cn.com/problems/number-of-operations-to-make-network-connected/
 * 问题思路转换一下：统计当前网络中所有并查集的个数
 * 联通m个并查集需要变动的线的个数为m-1
 * 联通n个计算机需要最小的线的个数为n-1，如果线缆数量小于n-1，那么需要返回-1
 */
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
 * leetcode 959. 由斜杠划分区域
 * https://leetcode-cn.com/problems/regions-cut-by-slashes/
 * 并查集
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