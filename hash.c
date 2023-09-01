#include <stdio.h>
#include "uthash.h"
#include <stdbool.h>

// https://leetcode.cn/problems/valid-anagram/
// 有效的字母异位词
bool isAnagram(char * s, char * t) {
    int hash[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        hash[s[i] - 'a']++;
    }
    len = strlen(t);
    for (int i = 0; i < len; i++) {
        hash[t[i] - 'a']--;
    }

    for(int i = 0; i < 26; i++) {
        if (hash[i] != 0) {
            return false;
        }
    }
    return true;
}

// https://leetcode.cn/problems/intersection-of-two-arrays/
// 两个数组的交集
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int nums[1001] = {0};
    int minLen = nums1Size > nums2Size ? nums2Size : nums1Size;

    int *ans = (int *)malloc(sizeof(int) * minLen);
    for (int i = 0; i < nums1Size; i++) {
        nums[nums1[i]]++;
    }

    *returnSize = 0;
    for (int i = 0; i < nums2Size; i++) {
        if (nums[nums2[i]] != 0) {
            ans[(*returnSize)++] = nums2[i];
            nums[nums2[i]] = 0;
        }       
    }

    return ans;
}

// hash
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
        hashAdd(nums1[nums1Size]);
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

// https://leetcode.cn/problems/3sum/
// 三数之和
int **ans = NULL;
int retSize = 0;
int *retColSize = NULL;

int *path = NULL;
int pathSize = 0;
int sum = 0;

void dfs(int *nums, int len, int startIndex) {
    if (pathSize == 3) {
        if (sum == 0) {
            int *tmp = (int *)malloc(sizeof(int) * 3);
            memcpy(tmp, path, sizeof(int) *3);
            ans[retSize] = tmp;
            retColSize[retSize++] = 3;
        }
        return; 
    }

    for (int i = startIndex; i < len; i++) {
        path[pathSize++] = nums[i];
        sum += nums[i];
        dfs(nums, len, i + 1);
        pathSize--;
        sum -= nums[i];
    }    
}
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes){
    ans = (int **)malloc(sizeof(int *) * 2001);
    path = (int *)malloc(sizeof(int) * 3);
    retColSize = (int *)malloc(sizeof(int) * 2001);

    dfs(nums, numsSize, 0);
    *returnSize = retSize;
    *returnColumnSizes = retColSize;

    return ans;
}