/*
 * 使用uhash or huawei list_hash解题题目搜录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "uhash/uthash.h"
#include "min_max.h"

/**
 * 692. 前K个高频单词
 * https://leetcode-cn.com/problems/top-k-frequent-words/
 * 使用uhash的哈希表进行哈希插入和查找
 */

#define MAX_WORD_LEN 100

struct wordTmpContainer {
    char *word;
    int times;
};

struct word_kv_hashnode {
    char word[MAX_WORD_LEN];
    int val;
    UT_hash_handle hh;
};

int cmpWordNode(const void *a, const void *b)
{
    struct wordTmpContainer *wa = (struct wordTmpContainer *)a;
    struct wordTmpContainer *wb = (struct wordTmpContainer *)b;

    if (wa->times == wb->times) {
        return strcmp(wa->word, wb->word) > 0;
    }

    return wa->times < wb->times;
}

char ** topKFrequent(char ** words, int wordsSize, int k, int* returnSize)
{
    char **ret = (char **)calloc(k, sizeof(char *));
    for (int i = 0; i < k; ++i) {
        ret[i] = (char *)calloc(MAX_WORD_LEN, sizeof(char *));
    }
    *returnSize = 0;

    struct wordTmpContainer *wn = (struct wordTmpContainer *)calloc(wordsSize, sizeof(struct wordTmpContainer));
    int wn_index = 0;

    struct word_kv_hashnode *s, *tmp;
    struct word_kv_hashnode *head = NULL;

    for (int i = 0 ; i < wordsSize; ++i) {
        HASH_FIND_STR(head, words[i], s);
        if (s) {
            s->val++;
        } else {
            s = (struct word_kv_hashnode *)calloc(1, sizeof(*s));
            strcpy(s->word, words[i]);
            s->val = 1;
            HASH_ADD_STR(head, word, s);
        }
    }
    
    HASH_ITER(hh, head, s, tmp) {
        wn[wn_index].word = s->word;
        wn[wn_index++].times = s->val;
    }

    qsort(wn, wn_index, sizeof(struct wordTmpContainer), cmpWordNode);
    for (int i = 0; i < k; ++i) {
        strcpy(ret[*returnSize], wn[i].word);
        (*returnSize)++;
    }

    HASH_ITER(hh, head, s, tmp) {
        HASH_DEL(head, s);
        free(s);
    }
    free(wn);

    return ret;
}

/**
 * 692. 前K个高频单词
 * https://leetcode-cn.com/problems/top-k-frequent-words/
 * 使用huawei list hash进行查找和插入
 */

typedef struct {
    char wordKey[MAX_WORD_LEN];
    int val;
    struct Node htNode;
} WordNode;

static bool inline nodeEqual(const struct Node *a, const struct Node *b)
{
    WordNode *na = NODE_ENTRY(a, WordNode, htNode);
    WordNode *nb = NODE_ENTRY(b, WordNode, htNode);
    return strcmp(na->wordKey, nb->wordKey) == 0;
}

static size_t inline nodeKey(const struct Node *node, size_t bktSize)
{
    WordNode *n = NODE_ENTRY(node, WordNode, htNode);
    size_t k = BkdrHash(n->wordKey);
    return k % bktSize;
}

void inSertToContainer(struct Node *node, void *arg)
{   
    struct argCombo {
        struct wordTmpContainer *container;
        int *index;
    };

    struct argCombo *args = (struct argCombo *)arg;

    WordNode *wn = NODE_ENTRY(node, WordNode, htNode);
    args->container[*(args->index)].times = wn->val;
    args->container[*(args->index)].word = wn->wordKey;
    (*args->index)++;
}

char ** topKFrequent2(char ** words, int wordsSize, int k, int* returnSize)
{
    char **ret = (char **)calloc(k, sizeof(char *));
    for (int i = 0; i < k; ++i) {
        ret[i] = (char *)calloc(MAX_WORD_LEN, sizeof(char *));
    }
    *returnSize = 0;

    struct wordTmpContainer *wc = (struct wordTmpContainer *)calloc(wordsSize, sizeof(struct wordTmpContainer));
    int wc_index = 0;
    struct HashTable ht;
    struct Node *n;
    WordNode cmp;

    size_t bktSize = 2048ull;
    (void)HashInit(&ht, bktSize, nodeEqual, nodeKey);

    for (int i = 0; i < wordsSize; ++i) {
        strcpy(cmp.wordKey, words[i]);
        n = HashFind(&ht, &cmp.htNode);
        if (n) {
            WordNode *wn = NODE_ENTRY(n, WordNode, htNode);
            wn->val++;
        } else {
            WordNode *newWn = (WordNode *)calloc(1, sizeof(WordNode));
            strcpy(newWn->wordKey, words[i]);
            newWn->val = 1;
            HashAdd(&ht, &newWn->htNode);
        }
    }

    struct argCombo {
        struct wordTmpContainer *container;
        int *index;
    };
    struct argCombo arg;
    arg.container = wc;
    arg.index = &wc_index;

    HashIterate(&ht, inSertToContainer, (void *)&arg);

    qsort(wc, wc_index, sizeof(struct wordTmpContainer), cmpWordNode);
    for (int i = 0; i < k; ++i) {
        strcpy(ret[*returnSize], wc[i].word);
        (*returnSize)++;
    }

    return ret;
}
