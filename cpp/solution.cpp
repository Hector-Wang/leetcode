
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
#include <cctype>
#include <cstring>
using namespace std;

class Solution {
public:

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

/*
 * 700. 二叉搜索树中的搜索
 * https://leetcode-cn.com/problems/search-in-a-binary-search-tree/
 */
    TreeNode* searchBST(TreeNode* root, int val) {
        if (!root) {
            return NULL;
        }
        if (root->val == val) {
            return root;
        }

        if (root->val > val) {
            return this->searchBST(root->left, val);
        }

        return this->searchBST(root->right, val);
    }


/*
 * 有效的数独
 * https://leetcode-cn.com/problems/valid-sudoku/
 * 验证每一横行、竖列、九宫格是否满足数独要求即可
 */ 
    bool isValidSudoku(vector<vector<char>>& board) {
        int assist[10];
        for (int i = 0; i < board.size(); ++i) {
            memset(assist, 0, sizeof(assist));
            for (int j = 0; j < board[0].size(); ++j) {
                if (isdigit(board[i][j])) {
                    assist[board[i][j] - '0']++;
                    if (assist[board[i][j] - '0'] > 1) {
                        return false;
                    }
                }
            }
        }

        for (int j = 0; j < board[0].size(); ++j) {
            memset(assist, 0, sizeof(assist));
            for (int i = 0; i < board.size(); ++i) {
                if (isdigit(board[i][j])) {
                    assist[board[i][j] - '0']++;
                    if (assist[board[i][j] - '0'] > 1) {
                        return false;
                    }
                }
            }
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                memset(assist, 0, sizeof(assist));
                for (int k = 0; k < 3; ++k) {
                    for (int m = 0; m < 3; ++m) {
                        if (isdigit(board[i * 3 + k][j * 3 + m])) {
                            assist[board[i * 3 + k][j * 3 + m] - '0']++;
                            if (assist[board[i * 3 + k][j * 3 + m] - '0'] > 1) {
                                return false;
                            }
                        }
                    }
                }
            }
        }

        return true;
    }
/*
 * 1588. 所有奇数长度子数组的和
 * https://leetcode-cn.com/problems/sum-of-all-odd-length-subarrays/
 * 前缀和
 */
    int sumOddLengthSubarrays(vector<int>& arr) {
        int sum = 0;
        int size = arr.size();
        vector<int> preSums(size + 1, 0);
        for (int i = 0; i < size; ++i) {
            preSums[i + 1] = preSums[i] + arr[i];
        }

        /* 对于每个元素，累加由该元素起始的 长度为1,3,5...的数组的和 */
        for (int start = 0; start < size; ++start) {
            for (int len = 1; start + len <= size; len += 2) {
                sum += preSums[start + len] - preSums[start];
            }
        }

        return sum;
    }

/*
 * 789. 逃脱阻碍者
 * https://leetcode-cn.com/problems/escape-the-ghosts/
 * 纯数学计算 比较距离即可
 */
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        int dis = abs(target[0]) + abs(target[1]);

        for (auto g : ghosts) {
            int gDis = abs(target[0] - g[0]) + abs(target[1] - g[1]);
            if (dis >= gDis) {
                return false;
            }
        }

        return true;
    }

/*
 * 443. 压缩字符串
 * https://leetcode-cn.com/problems/string-compression/
 */
    int compress(vector<char>& chars) {
        vector<char> res(chars.size(), 0);
        int resIdx = 0;
        int sameAlphaNum = 1;
        vector<int> tmpStack;
        for (int i = 0; i < chars.size(); ++i) {
            if (i == 0) {
                res[resIdx++] = chars[i];
            } else if (chars[i] != chars[i - 1]) {
                if (sameAlphaNum > 1) { 
                    while (sameAlphaNum > 0) {
                        tmpStack.push_back(sameAlphaNum % 10);
                        sameAlphaNum /= 10;
                    }
                    while (!tmpStack.empty()) {
                        res[resIdx++] = tmpStack.back() + '0';
                        tmpStack.pop_back();
                    }
                    sameAlphaNum = 1;
                }
                res[resIdx++] = chars[i];
            } else {
                sameAlphaNum++;
            }
        }
        if (sameAlphaNum > 1) { 
            while (sameAlphaNum > 0) {
                tmpStack.push_back(sameAlphaNum % 10);
                sameAlphaNum /= 10;
            }
            while (!tmpStack.empty()) {
                res[resIdx++] = tmpStack.back() + '0';
                tmpStack.pop_back();
            }
            sameAlphaNum = 1;
        }
        chars.clear();
        for (int i = 0; i < resIdx; ++i) {
            chars.push_back(res[i]);
        }
        return resIdx;
    }
};