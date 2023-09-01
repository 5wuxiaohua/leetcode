#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "uthash.h"

void stackSort(int *stack, int top) {
    int *help = (int *)malloc(sizeof(int) * top);
    int helpTop = 0;
    while (top != 0) {
        int cur = stack[--top];
        while (helpTop != 0 && cur < help[helpTop - 1]) {
            stack[top++] = help[--helpTop];
        }
        help[helpTop++] = cur;
    }
    
    while (helpTop != 0) {
        stack[top++] = help[--helpTop];
    }

    free(help);
}

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
                printf("i:%d, j:%d, len:%d\n", i, j, len);
                minLen = minLen < len ? minLen : len;
            }
        }
    }
    return minLen == INT_MAX ? 0 : minLen;
}

typedef struct hashTable {
    int key;
    UT_hash_handle hh;
} hashTable;

hashTable *hashSet = NULL;

hashTable *hashFind(int key) {
    hashTable *set = NULL;
    HASH_FIND_INT(hashSet, &key, set);
    return set;
}

void hashAdd(int key) {
    hashTable *set = NULL;
    HASH_FIND_INT(hashSet, &key, set);
    if (set == NULL) {
        set = (hashTable *)malloc(sizeof(hashTable));
        set->key = key;
        HASH_ADD_INT(hashSet, key, set);
    }   
}

int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int len = nums1Size < nums2Size ? nums1Size : nums2Size;
    int *ans = (int *)malloc(sizeof(int) * (len));
    for (int i = 0; i < nums1Size; i++) {
        hashAdd(nums1[i]);
    }

    for (int i = 0; i < nums2Size; i++) {
        hashTable *set = hashFind(nums2[i]);
        if (set != NULL) {
            ans[(*returnSize)++] = nums2[i];
            HASH_DEL(hashSet, set);
        }
    }
    return ans;
}

int main() {
    int nums1[3] = {4,9,5};
    int nums2[5] = {9,4,9,8,4};
    int ret = 0;
    int *ans = intersection(nums1, 3, nums2, 5, &ret);
    for (int i = 0; i < ret; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}