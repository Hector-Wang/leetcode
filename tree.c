/*
 * 二叉树/树类题目收录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"

/*
 * 993. 二叉树的堂兄弟节点
 * https://leetcode-cn.com/problems/cousins-in-binary-tree/
 * 遍历二叉树，记录两个节点的层次信息以及父节点信息，比较即可
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct levelInfo {
    int level;
    struct TreeNode *f;
};

void TraverseTree(struct TreeNode *root, int x, int y, struct levelInfo *levelX, struct levelInfo *levelY, int curLevel, struct TreeNode *f)
{
    if (root == NULL) {
        return;
    }
    if (root->val == x) {
        levelX->level = curLevel;
        levelX->f = f;
    }
    if (root->val == y) {
        levelY->level = curLevel;
        levelY->f = f;
    }

    TraverseTree(root->left, x, y, levelX, levelY, curLevel + 1, root);
    TraverseTree(root->right, x, y, levelX, levelY, curLevel + 1, root);
}

bool isCousins(struct TreeNode* root, int x, int y){
    struct levelInfo levelX = {0};
    struct levelInfo levelY = {0};
    TraverseTree(root, x, y, &levelX, &levelY, 0, NULL);
    return levelX.level == levelY.level && levelX.f != levelY.f;
}