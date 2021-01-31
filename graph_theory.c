/*
 * 图论题目搜录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"


/*
 * 1631. 最小体力消耗路径
 * https://leetcode-cn.com/problems/path-with-minimum-effort/
 * Dijkstra算法 寻求最短路径
 * Dijkstra算法 本质上是一个BFS搜索，只不过普通的BFS使用的是普通的队列，元素按照入队的顺序进行出队
 * Dijkstra需要使用优先队列，每次需要将权值（也就是距离起点的距离）最小的元素进行弹出，并进行遍历
 * 注意，因为还在队列中的元素，在其他元素弹出之后，其权值可能会发生变化，需要重新入队，从而会导致弹出顺序的变化
 * 所以这里不能在入队时判断元素是否被访问过，需要在出队时进行判断，这是和普通BFS的区别
 * 优先级队列使用小根堆实现
 * */
#define MAX_DIS 1000000
struct pathNode {
    int x;
    int y;
    int val;
};

int cmpNode(struct pathNode *a, struct pathNode *b)
{
    return a->val > b->val;
}

void minPathNodeHeapPush(struct pathNode heap[], struct pathNode x, int *heapSize)
{
    (*heapSize)++;
    heap[*heapSize] = x;
    int now = *heapSize;

    /* 进行交换，直到符合小根堆的特质，即所有的父节点都小于子节点 */
    while (now > 1) {
        int f = now >> 1;
        if (cmpNode(&heap[f], &heap[now])) {
            struct pathNode tmp = heap[f];
            heap[f] = heap[now];
            heap[now] = tmp;
        } else {
            break;
        }
        now = f;
    }
}

struct pathNode minPathNodeHeapPop(struct pathNode heap[], int *heapSize)
{
    /* 先交换堆顶和堆底 */
    struct pathNode tmp1 = heap[1];
    heap[1] = heap[*heapSize];
    heap[*heapSize] = tmp1;

    (*heapSize)--;

    int now = 1;
    while ((now << 1) <= *heapSize) {
        int c = now << 1;
        if (c + 1 <= *heapSize && !cmpNode(&heap[c + 1], &heap[c])) {
            c++;
        }
        /* 把较小的子节点与父节点交换 */
        if (cmpNode(&heap[now], &heap[c])) {
            struct pathNode tmp2 = heap[now];
            heap[now] = heap[c];
            heap[c] = tmp2;
        } else {
            break;
        }
        now = c;
    }
    return heap[(*heapSize) + 1];
}

int minimumEffortPath(int **heights, int heightsSize, int *heightsColSize)
{
    int disTable[heightsSize][heightsColSize[0]];
    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int visited[heightsSize][heightsColSize[0]];

    for (int i = 0; i < heightsSize; ++i) {
        for (int j = 0; j < heightsColSize[0]; ++j) {
            disTable[i][j] = MAX_DIS;
        }
    }
    memset(visited, 0, sizeof(visited));

    disTable[0][0] = 0;
    struct pathNode heap[heightsSize * heightsColSize[0] + 1];
    int heapSize = 0;
    struct pathNode zero = {
        .x = 0,
        .y = 0,
        .val = disTable[0][0],
    };
    minPathNodeHeapPush(heap, zero, &heapSize);

    while (heapSize > 0) {
        struct pathNode tmp = minPathNodeHeapPop(heap, &heapSize);
        if (visited[tmp.x][tmp.y]) {
            continue;
        }
        if ((tmp.x == heightsSize - 1) && (tmp.y == heightsColSize[0] - 1)) {
            break;
        }
        visited[tmp.x][tmp.y] = 1;
        for (int i = 0; i < 4; ++i) {
            int nextX = tmp.x + dir[i][0];
            int nextY = tmp.y + dir[i][1];
            if (nextX >= 0 && nextX < heightsSize && nextY >= 0 && nextY < heightsColSize[0]) {
                int nextDis = max(disTable[tmp.x][tmp.y], abs(heights[tmp.x][tmp.y] - heights[nextX][nextY]));
                if (nextDis < disTable[nextX][nextY]) {
                    disTable[nextX][nextY] = nextDis;
                    struct pathNode next = {
                        .x = nextX,
                        .y = nextY,
                        .val = disTable[nextX][nextY],
                    };
                    minPathNodeHeapPush(heap, next, &heapSize);
                }
            }
        }
    }

    return disTable[heightsSize - 1][heightsColSize[0] - 1];
}

/*
 * 778. 水位上升的泳池中游泳
 * https://leetcode-cn.com/problems/swim-in-rising-water/
 * 与上题同理，也是使用Dijkstra算法寻求最短路径
 * 只不过这一题的路径变成了，与0的差值的最小值
 */

int swimInWater(int** grid, int gridSize, int* gridColSize)
{
    int disTable[gridSize][gridColSize[0]];
    int visited[gridSize][gridColSize[0]];
    int dir[][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    
    int maxHeight = gridSize * gridSize;

    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridColSize[0]; ++j) {
            disTable[i][j] = maxHeight;
        }
    }
    disTable[0][0] = grid[0][0];

    memset(visited, 0, sizeof(visited));

    struct pathNode heap[gridSize * gridSize + 1];
    int heapSize = 0;
    
    struct pathNode start = { .x = 0, .y = 0, .val = disTable[0][0] };
    minPathNodeHeapPush(heap, start, &heapSize);
    

    while (heapSize > 0) {
        struct pathNode tmp = minPathNodeHeapPop(heap, &heapSize);
        if (visited[tmp.x][tmp.y]) {
            continue;
        }
        if ((tmp.x == gridSize - 1) && (tmp.y == gridColSize[0] - 1)) {
            break;
        }
        visited[tmp.x][tmp.y] = 1;

        for (int i = 0; i < 4; ++i) {
            int nextX = tmp.x + dir[i][0];
            int nextY = tmp.y + dir[i][1];

            if (nextX >= 0 && nextX < gridSize && nextY >= 0 && nextY < gridColSize[0]) {
                int nextDis = max(grid[nextX][nextY], tmp.val);
                if (nextDis < disTable[nextX][nextY]) {
                    disTable[nextX][nextY] = nextDis;
                    struct pathNode next = { .x = nextX, .y = nextY, .val = disTable[nextX][nextY] };
                    minPathNodeHeapPush(heap, next, &heapSize);
                }
            }
        }
    }
    return disTable[gridSize - 1][gridColSize[0] - 1];
}