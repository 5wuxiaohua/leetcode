#include <stdbool.h>
#include <stdio.h>

typedef struct Node{
    int value;
    struct Node *next;
    struct Node *left;
    struct Node *right;   
} Node;

struct Node* connect(struct Node* root) {
    Node **queue = (Node **)malloc(sizeof(Node *) * 5001);
    int head = 0;
    int tail = 0;
    queue[tail++] = root;
    while (tail != head) {
        int size = tail - head;
        for (int i = 0; i < size; i++) {
            Node *temp = queue[head++];
            if (i < size - 1) temp->next = queue[head];
            if (temp->left) queue[tail++] = temp->left;
            if (temp->right) queue[tail++] = temp->right;
        }
    }

    return root;
}

int minSubArrayLen(int target, int* nums, int numsSize){
    int sum = 0;
    int j = 0;
    int minLen = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
        while (sum >= target) {
            int len = i - j + 1;
            minLen = minLen < len ? minLen : len;
            sum -= nums[j++];
        }
    }
    return minLen;
}

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

    for (int i = 0; i < 26; i++) {
        if (hash[i] != 0) return false;
    }
    return true;
}

int find(int *f, int x) {
    return x == f[x] ? x : find(f, f[x]);
}

bool merge(int *f, int *rank, int x, int y) {
    int fx = find(f, x), fy = find(f ,y);
    if (fx == fy) return false; 

    if (rank[fx] > rank[fy]) {
        f[fy] = fx;
        rank[fx] += rank[fy];
    } else {
        rank[fy] += rank[fx];
        f[fx] = fy;
    }
    return true;
}


bool dfs(struct Node *root, int targetSum) {
    if (root == NULL) return false;

    targetSum -= root->value;
    if (root->left == NULL && root->right == NULL && targetSum == 0) {
        return true;
    }

    return dfs(root->left, targetSum) || dfs(root->right, targetSum);
}

bool hasPathSum(struct Node* root, int targetSum) {
    if (root == NULL) return false;
    return dfs(root, targetSum);
}