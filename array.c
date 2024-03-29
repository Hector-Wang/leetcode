/*
 * 数组类题目搜录
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list_hash/hlist.h"
#include "list_hash/hhash.h"
#include "min_max.h"

/*
 * 989. 数组形式的整数加法
 * https://leetcode-cn.com/problems/add-to-array-form-of-integer/
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
 * 1128. 等价多米诺骨牌对的数量
 * https://leetcode-cn.com/problems/number-of-equivalent-domino-pairs/
 */
/* 暴力解法，超出时间限制 */
bool equal(int *dominoeA, int *dominoeB)
{
    return (dominoeA[0] == dominoeB[0] && dominoeA[1] == dominoeB[1]) ||
           (dominoeA[0] == dominoeB[1] && dominoeA[1] == dominoeB[0]);
}

int numEquivDominoPairsRough(int** dominoes, int dominoesSize, int* dominoesColSize)
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
 * 724. 寻找数组的中心索引
 * https://leetcode-cn.com/problems/find-pivot-index/
 */
int pivotIndex(int* nums, int numsSize)
{
    int sum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }

    int leftSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (leftSum * 2 + nums[i] == sum) {
            return i;
        }
        leftSum += nums[i];
    }

    return -1;
}

/*
 * 628. 三个数的最大乘积
 * https://leetcode-cn.com/problems/maximum-product-of-three-numbers/
 */
int cmp1(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int maximumProduct(int* nums, int numsSize){
    qsort(nums, numsSize, sizeof(int), cmp1);
    int maxForPos = nums[numsSize - 2] * nums[numsSize - 3];
    int maxForNeg = nums[0] * nums[1];
    if (nums[numsSize - 1] > 0) {
        return max(maxForNeg, maxForPos) * nums[numsSize - 1];
    } else {
        return min(maxForNeg, maxForPos) * nums[numsSize - 1];
    }

}


/*
 * 888. 公平的糖果棒交换
 * https://leetcode-cn.com/problems/fair-candy-swap/
 */
int cmp2(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int* fairCandySwap(int* A, int ASize, int* B, int BSize, int* returnSize)
{
    int *ret = (int *)calloc(2, sizeof(int));
    int ASum = 0, BSum = 0;
    *returnSize = 2;
    
    for (int i = 0; i < ASize; ++i) {
        ASum += A[i];
    }
    for (int i = 0; i < BSize; ++i) {
        BSum += B[i];
    }

    qsort(A, ASize, sizeof(int), cmp2);
    qsort(B, BSize, sizeof(int), cmp2);

    int largerSize = ASum > BSum ? ASize : BSize;
    int smallerSize = ASum < BSum ? ASize : BSize;
    int diff = abs(BSum - ASum);
    int *largerPtr = ASum > BSum ? A : B;
    int *smallerPtr = ASum < BSum ? A : B;

    int i = 0, j = 0;
    for (; i < smallerSize; ++i) {
        for (; j < largerSize; ++j) {
            if (smallerPtr[i] >= largerPtr[j]) {
                continue;
            }
            if ((largerPtr[j] - smallerPtr[i]) * 2 == diff) {
                ret[0] = ASum > BSum ? largerPtr[j] : smallerPtr[i];
                ret[1] = ASum > BSum ?  smallerPtr[i] : largerPtr[j];
                return ret;
            } else if ((largerPtr[j] - smallerPtr[i]) * 2 > diff) {
                break;
            }
        }
    }
    return ret;
}


/*
 * 119. 杨辉三角 II
 * https://leetcode-cn.com/problems/pascals-triangle-ii/
 */
int* getRow(int rowIndex, int* returnSize)
{
    int *ret = (int *)calloc(rowIndex + 1, sizeof(int));
    *returnSize = rowIndex + 1;

    for (int i = 0; i <= rowIndex; ++i) {
        for (int j = i; j >= 0; --j) {
            if (j == 0) {
                ret[j] = 1;
                continue;
            }
            if (j == i) {
                ret[j] = 1;
                continue;
            }
            ret[j] = ret[j - 1] + ret[j];
        }
    }
    return ret;
}

/*
 * 832. 翻转图像
 * https://leetcode-cn.com/problems/flipping-an-image/
 */
int** flipAndInvertImage(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes)
{
    int **ret = (int **)calloc(ASize, sizeof(int *));
    *returnSize = ASize;
    *returnColumnSizes = (int *)calloc(ASize, sizeof(int));

    for (int i = 0; i < ASize; ++i) {
        ret[i] = (int *)calloc(AColSize[i], sizeof(int));
        (*returnColumnSizes)[i] = AColSize[i];
        for (int j = 0; j < AColSize[i]; ++j) {
            ret[i][j] = A[i][AColSize[i] - 1 - j] ^ 1;
        }
    }
    return ret;
}

/*
 * 304. 二维区域和检索 - 矩阵不可变
 * https://leetcode-cn.com/problems/range-sum-query-2d-immutable/
 * 使用前缀和
 */
typedef struct {
    int **matrixSum;
    int matrixSize;
    int *matrixColSize;
} NumMatrix;

NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize)
{
    if (!matrix || !matrixSize || !matrixColSize) {
        return NULL;
    }
    
    NumMatrix *obj = (NumMatrix *)calloc(1, sizeof(NumMatrix));
    obj->matrixSum = (int **)calloc(matrixSize, sizeof(int *));
    obj->matrixColSize = (int *)calloc(matrixSize, sizeof(int));
    if (!obj || !obj->matrixSum || !obj->matrixColSize) {
        return NULL;
    }
    obj->matrixSize = matrixSize;

    for (int i = 0; i < matrixSize; ++i) {
        obj->matrixSum[i] = (int *)calloc(matrixColSize[i], sizeof(int));
        obj->matrixColSize[i] = matrixColSize[i];
        for (int j = 0; j < matrixColSize[i]; ++j) {
            obj->matrixSum[i][j] = j == 0 ? matrix[i][j] : (obj->matrixSum[i][j - 1] + matrix[i][j]);
        }
    }

    return obj;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2)
{
    if (!obj || !obj->matrixSum || !obj->matrixSize || !obj->matrixColSize) {
        return 0;
    }

    if (row1 > row2 || col1 > col2) {
        return 0;
    }

    if (row1 < 0 || row2 >= obj->matrixSize || col1 < 0 || col2 >= obj->matrixColSize[0]) {
        return 0;
    }

    int res = 0;

    for (int i = row1; i <= row2; ++i) {
        res += obj->matrixSum[i][col2] - (col1 > 0 ? obj->matrixSum[i][col1 - 1] : 0);
    }

    return res;
}

void numMatrixFree(NumMatrix* obj)
{
    if (!obj) {
        return;
    }
    
    if (obj->matrixSum) {
        for (int i = 0; i < obj->matrixSize; ++i) {
            free(obj->matrixSum[i]);
        }
        free(obj->matrixSum);
    }
    free(obj->matrixColSize);
    free(obj);
}

/*
 * 303. 区域和检索 - 数组不可变
 * https://leetcode-cn.com/problems/range-sum-query-immutable/
 * 使用前缀和
 */
typedef struct {
    int *arraySum;
    int arraySize;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize)
{
    if (!nums || !numsSize) {
        return NULL;
    }

    NumArray *obj = (NumArray *)calloc(1, sizeof(NumArray));
    if (!obj) {
        return NULL;
    }

    obj->arraySum = (int *)calloc(numsSize + 1, sizeof(int));
    if (!obj->arraySum) {
        return NULL;
    }

    obj->arraySize = numsSize;

    for (int i = 0; i < numsSize; ++i) {
        obj->arraySum[i + 1] = obj->arraySum[i] + nums[i];
    }
    return obj;
}

int numArraySumRange(NumArray* obj, int i, int j)
{
    if (!obj || !obj->arraySum || !obj->arraySize) {
        return 0;
    }

    if (i > j) {
        return 0;
    }

    if (i < 0 || j >= obj->arraySize) {
        return 0;
    }

    return obj->arraySum[j + 1] - obj->arraySum[i];
}

void numArrayFree(NumArray* obj)
{
    if (!obj) {
        return;
    }
    if (obj->arraySum) {
        free(obj->arraySum);
    }

    free(obj);
}

/*
 * 456. 132 模式
 * https://leetcode-cn.com/problems/132-pattern/
 * 暴力解法, 此题还可以用单调栈的做法求解，解法参考
 * https://leetcode-cn.com/problems/132-pattern/solution/fu-xue-ming-zhu-cong-bao-li-qiu-jie-dao-eg78f/
 */

bool find132pattern(int* nums, int numsSize)
{
    if (!nums || numsSize < 3) {
        return false;
    }

    int leftMin = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[j] > leftMin && nums[j] < nums[i]) {
                return true;
            }
        }
        leftMin = min(leftMin, nums[i]);
    }
    return false;
}

/*
 * 154. 寻找旋转排序数组中的最小值 II
 * https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/
 */
int findMin(int* nums, int numsSize)
{
    int ret = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[i - 1]) {
            return nums[i];
        }
    }
    return ret;
}

/*
 * 153. 寻找旋转排序数组中的最小值
 * https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/
 */
int findMinI(int* nums, int numsSize)
{
    int ret = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[i - 1]) {
            return nums[i];
        }
    }
    return ret;
}

/*
 * 81. 搜索旋转排序数组 II
 * https://leetcode-cn.com/problems/search-in-rotated-sorted-array-ii/
 * 先寻找边界，再二分查找
 */
int findEdge(int *nums, int numsSize)
{
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] < nums[i - 1]) {
            return i;
        }
    }
    return 0;
}

bool findInEdge(int *nums, int target, int left, int right)
{
    int middle;
    if (left > right) {
        return false;
    } else if (left == right) {
        if (target == nums[left]) {
            return true;
        } else {
            return false;
        }
    }

    while (left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] == target) {
            return true;
        }
        if (nums[middle] > target) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return false;
}

bool search(int* nums, int numsSize, int target)
{
    int edge = findEdge(nums, numsSize);
    if (nums[edge] == target) {
        return true;
    } else {
        return findInEdge(nums, target, 0, edge - 1) || findInEdge(nums, target, edge + 1, numsSize - 1);
    }
}

/*
 * 80. 删除有序数组中的重复项 II
 * https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array-ii/
 */
int removeDuplicates(int* nums, int numsSize)
{
    if (!nums || !numsSize) {
        return 0;
    }

    int ret = numsSize;
    int dupTimes = 0;
    int i = 1;
    while (i < numsSize) {
        if (nums[i] == nums[i - 1]) {
            dupTimes++;
            if (dupTimes > 1) {
                memmove(&nums[i], &nums[i + 1], (numsSize - i - 1) * sizeof(int));
                numsSize--;
                ret = numsSize;
                dupTimes--;
                continue;
            }
        } else {
            dupTimes = 0;
        }
        i++;
    }
    return ret;
}

/*
 * 781. 森林中的兔子
 * https://leetcode-cn.com/problems/rabbits-in-forest/
 * 先排序，相邻相同的元素代表颜色相同的兔子，但是相同颜色兔子的个数不能大于当前这组元素的个数
 */
int cmpRabbits(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int numRabbits(int* answers, int answersSize)
{
    if (!answers || answersSize <= 0) {
        return 0;
    }

    int ret, currentLen;
    
    qsort(answers, answersSize, sizeof(int), cmpRabbits);
    
    ret = answers[0] + 1;
    currentLen = 0;

    for (int i = 1; i < answersSize; ++i) {
        if (answers[i] == answers[i - 1] && currentLen < answers[i]) {
            currentLen++;
            continue;
        }
        currentLen = 0;
        ret += (answers[i] + 1);
    }

    return ret;
}

/*
 * 645. 错误的集合
 * https://leetcode-cn.com/problems/set-mismatch/
 */

static int cmpFindErrorNums(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int* findErrorNums(int* nums, int numsSize, int* returnSize)
{
    int i;

    if (!nums || !numsSize) {
        return NULL;
    }

    *returnSize = 2;
    int *ret = (int *)calloc(*returnSize, sizeof(int));

    qsort(nums, numsSize, sizeof(int), cmpFindErrorNums);

    for (i = 1; i < numsSize; ++i) {
        if (nums[i] == nums[i - 1]) {
            ret[0] = nums[i];
            nums[i] = 0;
            break;
        }
    }
    
    if (i < numsSize - 1) {
        memmove(nums + i, nums + i + 1, (numsSize - i - 1) * sizeof(int));
    }

    numsSize--;

    qsort(nums, numsSize, sizeof(int), cmpFindErrorNums);

    for (i = 0; i < numsSize; ++i) {
        if (nums[i] != i + 1) {
            ret[1] = i + 1;
            break;
        }
    }

    if (i == numsSize) {
        ret[1]  = i + 1;
    }

    return ret;
}


/*
 * 451. 根据字符出现频率排序
 * https://leetcode-cn.com/problems/sort-characters-by-frequency/
 */

struct charNode {
    char c;
    int times;
};

int cmpFrequencySort(const void *a, const void *b)
{
    struct charNode *na = (struct charNode *)a;
    struct charNode *nb = (struct charNode *)b;
    if (na->times == nb->times) {
        return na->c < nb->c;
    } else {
        return na->times < nb->times;
    }
}

char * frequencySort(char * s)
{
    int freq[256] = {0};
    int sLen = strlen(s);
    char *ret = (char *)calloc(sLen + 1, sizeof(char));
    struct charNode *stringNode = (struct charNode *)calloc(sLen, sizeof(struct charNode));

    for (int i = 0; i < sLen; ++i) {
        ++freq[s[i]];
    }

    for (int i = 0; i < sLen; ++i) {
        stringNode[i].c = s[i];
        stringNode[i].times = freq[s[i]];
    }

    qsort(stringNode, sLen, sizeof(struct charNode), cmpFrequencySort);

    for (int i = 0; i < sLen; ++i) {
        ret[i] = stringNode[i].c;
    }

    free(stringNode);
    return ret;
}

/*
 * 面试题 10.02. 变位词组
 * https://leetcode-cn.com/problems/group-anagrams-lcci/
 * 最后一个用例超时
 */
void cpyToRetArray(char **retStr, char *inputStr, int *returnColumeSizes, int columeIndex)
{
    *retStr = (char *)calloc(strlen(inputStr) + 1, sizeof(char));
    strcpy(*retStr, inputStr);
    returnColumeSizes[columeIndex]++;
}

int cmpHeadStr(char *first, char *second)
{
#define ALPHABET_LEN 26
    int record[ALPHABET_LEN] = {0};
    int fisrtLen = strlen(first);
    int sencondLen = strlen(second);
    if (fisrtLen != sencondLen) {
        return -1;
    }

    for (int i = 0; i < fisrtLen; ++i) {
        record[first[i] - 'a']++;
    }

    for (int i = 0; i < sencondLen; ++i) {
        record[second[i] - 'a']--;
    }

    for (int i = 0; i < ALPHABET_LEN; ++i) {
        if (record[i] != 0) {
            return -1;
        }
    }

    return 0;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes)
{
    bool copyFlag = false;
    if (!strs || strsSize <= 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    char ***ret = (char ***)calloc(strsSize, sizeof(char **));

    for (int i = 0; i < strsSize; ++i) {
        ret[i] = (char **)calloc(strsSize, sizeof(char*));
    }

    *returnColumnSizes = (int *)calloc(strsSize, sizeof(int));
    *returnSize = 0;

    cpyToRetArray(&ret[0][0], strs[0], *returnColumnSizes, 0);
    (*returnSize)++;
    for (int i = 1; i < strsSize; ++i) {
        copyFlag = false;
        for (int j = 0; j < *returnSize; ++j) {
            if (cmpHeadStr(strs[i], ret[j][0]) == 0) {
                cpyToRetArray(&ret[j][(*returnColumnSizes)[j]], strs[i], *returnColumnSizes, j);
                copyFlag = true;
                break;
            }
        }
        if (!copyFlag) {
            cpyToRetArray(&ret[*returnSize][0], strs[i], *returnColumnSizes, *returnSize);
            (*returnSize)++;
        }
    }

    return ret;
}

