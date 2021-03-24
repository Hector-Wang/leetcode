#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"

/*
 * 思路：哈希表 + 双向链表
 * key,val数据对，同时存在于哈希表和双向链表中
 * 哈希表用来搞定时间复杂度为O(1)的访问
 * 双向链表完成最近访问的更新（删除节点->向尾部插入）
 * cache满了之后，只需要删除链表头（最远访问的节点），便可以完成新元素的插入
 * 使用list和hash数据结构，可以完成node节点和hash表以及链表的关联，不需要自己再实现链表的增删改查
 */
typedef struct {
    int capacity;
    int curNodeNum;
    struct HashTable ht;
    struct List doubleList;
} LRUCache;

typedef struct {
    int key;
    int value;
    struct Node htNode;
    struct Node listNode;
} LRUNode;

static bool inline nodeEqual(const struct Node *a, const struct Node *b)
{
    LRUNode *na = NODE_ENTRY(a, LRUNode, htNode);
    LRUNode *nb = NODE_ENTRY(b, LRUNode, htNode);
    return na->key == nb->key;
}

static size_t inline nodeKey(const struct Node *node, size_t bktSize)
{
    LRUNode *n = NODE_ENTRY(node, LRUNode, htNode);
    size_t k = TwIntHash((unsigned int)(n->key));
    return k % bktSize;
}

LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache = (LRUCache *)calloc(1, sizeof(LRUCache));
    if (!cache) {
        return cache;
    }
    cache->capacity = capacity;
    cache->curNodeNum = 0;
    ListInit(&cache->doubleList);
    size_t bktSize = (size_t)capacity;
    int ret = HashInit(&cache->ht, bktSize, nodeEqual, nodeKey);
    if (ret) {
        free(cache);
        return NULL;
    }
    return cache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    LRUNode cmp = {
        .key = key
    };
    struct Node *n = HashFind(&obj->ht, &cmp.htNode);
    if (!n) {
        return -1;
    }

    LRUNode *ln = NODE_ENTRY(n, LRUNode, htNode);
    ListRemove(&ln->listNode);
    ListAddTail(&obj->doubleList, &ln->listNode);
    return ln->value;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    LRUNode cmp = {
        .key = key
    };
    LRUNode *ln;
    struct Node *n = HashFind(&obj->ht, &cmp.htNode);
    if (n) {
        ln = NODE_ENTRY(n, LRUNode, htNode);
        ln->value = value;
        ListRemove(&ln->listNode);
        ListAddTail(&obj->doubleList, &ln->listNode);
        HashRemove(&ln->htNode);
        HashAdd(&obj->ht, &ln->htNode);
    } else {
        if (obj->curNodeNum < obj->capacity) {
            ln = (LRUNode *)calloc(1, sizeof(LRUNode));
            obj->curNodeNum++;
        } else {
            ln = LIST_HEAD_ENTRY(&obj->doubleList, LRUNode, listNode);
            if (ln == NULL) {
                return;
            }
            ListRemove(&ln->listNode);
            HashRemove(&ln->htNode);
        }
        ln->key = key;
        ln->value = value;
        ListAddTail(&obj->doubleList, &ln->listNode);
        HashAdd(&obj->ht, &ln->htNode);
    }
}

static void FreeNode(struct Node *node)
{
    LRUNode *ln = NODE_ENTRY(node, LRUNode, listNode);
    free(ln);
}

void lRUCacheFree(LRUCache *obj)
{
    HashDeinit(&obj->ht, NULL);
    ListDeinit(&obj->doubleList, FreeNode);
    free(obj);
}