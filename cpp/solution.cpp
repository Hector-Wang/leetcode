
#include <vector>
#include <queue>
#include <climits>
#include <cmath>
using namespace std;

class Solution {
public:
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