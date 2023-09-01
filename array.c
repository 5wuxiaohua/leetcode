#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// https://leetcode.cn/problems/remove-element/
// 移出数组中值为val的元素
int removeElement(int* nums, int numsSize, int val){
    int flow = 0;
    int fast = 0;

    for (fast = 0; fast < numsSize; fast++) {
        if (nums[fast] != val) {
            nums[flow++] = nums[fast];
        }
    }
    return flow;
}

int removeElement(int *nums, int numsSize, int val) {
    int flow = 0;
    int fast = 0;

    while (fast < numsSize) {
        if (nums[fast] != val) {
            nums[flow++] = nums[fast++];
        } else {
            fast++;
        }
    }
    
    return flow;
}

// https://leetcode.cn/problems/squares-of-a-sorted-array/
// 非递减数组的平方排序
int* sortedSquares(int* nums, int numsSize, int* returnSize){
    int *ans = (int *)malloc(sizeof(int) * numsSize);
    int i = 0;
    int j = numsSize - 1;
    int k = numsSize - 1;
    while (i <= j) {
        if (fabs(nums[i]) <= fabs(nums[j])) {
            ans[k--] = nums[j] * nums[j];
            j--;
        } else {
            ans[k--] = nums[i] * nums[i];
            i++;
        }
    }
    *returnSize = numsSize;
    return ans;
}

// https://leetcode.cn/problems/minimum-size-subarray-sum/
// 长度最小子数组

// 暴力破解
int minSubArrayLen(int target, int* nums, int numsSize){
    int sum = 0;
    int minLen = INT_MAX;
    int len = 0;

    for (int i = 0; i < numsSize; i++) {
        sum = 0;
        int j = 0;
        for (j = i; j < numsSize; j++) {
            sum += nums[j];
            if (sum >= target) {
                len = j - i + 1;
                minLen = minLen < len ? minLen : len;
            }
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}

// 滑动窗口
int minSubArrayLen(int target, int* nums, int numsSize){
    int sum = 0;
    int j = 0;
    int minLen = INT_MAX;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        while (sum >= target) {
            int len = i - j + 1;
            minLen = minLen < len ? minLen : len;
            sum -= nums[j++];
        } 
    }
    return minLen == INT_MAX ? 0 : minLen;
}