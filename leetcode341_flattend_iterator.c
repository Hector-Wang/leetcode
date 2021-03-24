#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"

/**
 * *********************************************************************
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * *********************************************************************
 *
 * // Return true if this NestedInteger holds a single integer, rather than a nested list.
 * bool NestedIntegerIsInteger(struct NestedInteger *);
 *
 * // Return the single integer that this NestedInteger holds, if it holds a single integer
 * // The result is undefined if this NestedInteger holds a nested list
 * int NestedIntegerGetInteger(struct NestedInteger *);
 *
 * // Return the nested list that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * struct NestedInteger **NestedIntegerGetList(struct NestedInteger *);
 *
 * // Return the nested list's size that this NestedInteger holds, if it holds a nested list
 * // The result is undefined if this NestedInteger holds a single integer
 * int NestedIntegerGetListSize(struct NestedInteger *);
 * };
 * 
 * https://leetcode-cn.com/problems/flatten-nested-list-iterator/
 */
#if 0
#define MAX_SIZE 50000
struct NestedIterator {
    int nestedIntVal[MAX_SIZE];
    int nestedIntLen;
    int nestedIntIndex;
};

void createHelper(struct NestedInteger** nestedList, int nestedListSize, struct NestedIterator *it)
{
    if (!nestedList || nestedListSize <= 0) {
        return;
    }
    if (NestedIntegerIsInteger(*nestedList)) {
        it->nestedIntVal[it->nestedIntLen++] = NestedIntegerGetInteger(*nestedList);
        createHelper(nestedList + 1, nestedListSize - 1, it);
    } else {
        struct NestedInteger **flattenedList = NestedIntegerGetList(*nestedList);
        int flattenedListSize = NestedIntegerGetListSize(*nestedList);
        createHelper(flattenedList, flattenedListSize, it);
        createHelper(nestedList + 1, nestedListSize - 1, it);
    }
}

struct NestedIterator *nestedIterCreate(struct NestedInteger** nestedList, int nestedListSize) {
    struct NestedIterator *it = (struct NestedIterator *)calloc(1, sizeof(struct NestedIterator));
    createHelper(nestedList, nestedListSize, it);
    return it;
}

bool nestedIterHasNext(struct NestedIterator *iter) {
    return iter->nestedIntIndex < iter->nestedIntLen;
}

int nestedIterNext(struct NestedIterator *iter) {
    return iter->nestedIntVal[iter->nestedIntIndex++];
}

/** Deallocates memory previously allocated for the iterator */
void nestedIterFree(struct NestedIterator *iter) {
    free(iter);
}
#endif