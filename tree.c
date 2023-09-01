#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
// https://leetcode.cn/problems/maximum-width-of-binary-tree/solutions/
// 二叉树最大宽度
typedef struct TreeNode TreeNode;
typedef struct queue {
    TreeNode *node;
    unsigned long long  index;
} queue;

queue queueTree[3000] = {0};


int widthOfBinaryTree(struct TreeNode* root){
    int head = 0;
    int tail = 0;
    int ret = 0;
    queueTree[tail].node = root;
    queueTree[tail++].index = 0;
    while (tail - head > 0) {
        int size = tail - head;
        int len = queueTree[tail - 1].index - queueTree[head].index + 1;
        ret = ret > len ? ret : len;
        for (int i = 0; i < size; i++) {
            queue temp = queueTree[head];
            unsigned long long  index = queueTree[head++].index;
            if (temp.node->left) {
                queueTree[tail].node = temp.node->left;
                queueTree[tail++].index = temp.index * 2 + 1;
            }

            if (temp.node->right) {
                queueTree[tail].node = temp.node->right;
                queueTree[tail++].index = temp.index * 2 + 2;
            }

        }
    }

    return ret;
}