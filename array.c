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