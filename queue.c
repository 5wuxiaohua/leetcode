#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"

// https://leetcode.cn/problems/sliding-window-maximum/description/
// 滑动窗口最大值
int queue[100000];
int head = 0;
int tail = 0;

void push(int data) {
    while ((tail - head) > 0 && data > queue[tail - 1]) {
        tail--;
    }
    queue[tail++] = data;
}

void pop(int data) {
    if ((tail - head) > 0 && data == queue[head]) {
        head++;
    }
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    int *ans = (int *)malloc(sizeof(int) * (numsSize - k + 1));
    int retSize = 0;
    head = 0;
    tail = 0;
    for (int i = 0; i < k; i++) {
        push(nums[i]);
    }
    ans[retSize++] = queue[head];

    for (int i = k; i < numsSize; i++) {
        pop(nums[i - k]);
        push(nums[i]);
        ans[retSize++] = queue[head];
    }

    *returnSize = retSize;
    return ans;
}

// https://leetcode.cn/problems/top-k-frequent-elements/
// 前 K 个高频元素
typedef struct hashTable {
    int key;
    int value;
    UT_hash_handle hh;
} hashTable;

hashTable *hashMap = NULL;
hashTable *find(int key) {
    hashTable *temp = NULL;
    HASH_FIND_INT(hashMap, &key, temp);
    return temp;
}

void add(int key, int value) {
    hashTable *temp = find(key);
    if (temp == NULL) {
        temp = (hashTable *)malloc(sizeof(hashTable));
        temp->key = key;
        temp->value = value;
        HASH_ADD_INT(hashMap, key, temp);
        return;
    }
    temp->value++;
    return;
}

typedef struct heap {
    int key;
    int value;
} heap;

heap *heapData = NULL;
int heapSize = 0;
void heapPush(hashTable *node) {
    heapData[heapSize].key = node->key;
    heapData[heapSize++].value = node->value;

    int son = heapSize - 1;
    while (son) {
        int father = son/2;
        if (heapData[father].value <= heapData[son].value) {
            return;
        }
        swap(heapData[father].value, heapData[son].value);
        son = father;            
    }
}

void heapPop() {
    heapData[0] = heapData[heapSize - 1];
    heapSize--;

    int father = 0;
    while (2*father + 1 < heapSize) {
        int son = 2*father + 1;
        if (heapData[son].value < heapData[son + 1].value) son++;
         
        if (heapData[father].value <= heapData[son].value) {
            return;
        }
        swap(heapData[father].value, heapData[son].value);
        father = son;            
    }
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize){
    heapData = (heap *)malloc(sizeof(heap) * k);
    for (int i = 0; i < numsSize; i++) {
        add(nums[i], i);
    }

    hashTable *p, *tmp;
    HASH_ITER(hh, hashTable, p, tmp) {
        if (heapSize == k - 1) {
            heap temp = heapData[0];
            if (temp.value < p->value) {
                heapPop();
                heapPush(p);
            }
        } else {
            heapPush(p);
        }
    }

    *returnSize = k;
    int *ans = (int *)malloc(sizeof(int) * k);
    for (int i = 0; i < k; i++) {
        ans[i] = heapData[i].key;
    }

    return ans;

}