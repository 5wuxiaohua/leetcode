#include <stdio.h>

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int binaryFind(int *nums, int len, int target) {
    int left = 0;
    int right = len - 1;

    while (left < right) {
        int mid = left + (right - left)/2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else {
            return mid;
        }
    }

    return -1;
}

void quickSort(int *nums, int left, int right) {
    if (left < right) {
        return;
    }

    int i = left;
    int j = right;
    int key = nums[i];
    while (i < j) {
        while (i < j && nums[j] > key) {
            j--;
        }
        nums[i] = nums[j];

        while (i < j && nums[i] < key) {
            i++;
        }
        nums[j] = nums[i];

    }
    nums[i] = key;

    quickSort(nums, left, i - 1);
    quickSort(nums, i + 1, right);
}

void insertSort(int *nums, int len) {
    for (int i = 1; i < len; i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key) {
            nums[j + 1] = nums[j];
            j--;
        }
        nums[j + 1] = key;
    }
}

void adjustHeap(int *nums, int father, int len) {
    while (2*father + 1 < len) {
        int son = 2*father + 1;
        if (son + 1 < len && nums[son] < nums[son + 1]) {
            son++;
        }

        if (nums[father] >= nums[son]) {
            return;
        }
        if (nums[father] < nums[son]) {
            swap(&nums[father], &nums[son]);
            father = son;
        }  
    }
}
void buildHeap(int *nums, int len) {
    for (int i = len/2 - 1; i >= 0; i--) {
        adjustHeap(nums, i, len);
    } 
}

void heapSort(int *nums, int len) {
    for (int i = len; i > 1; i--) {
        buildHeap(nums, i);
        swap(&nums[0], &nums[i - 1]);
    }
}

