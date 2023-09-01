#include <stdio.h>
#include <stdbool.h>

// https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/description/

// Definition for a Node.
typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} Node;



struct Node* connect(struct Node* root) {
	if (root == NULL) return NULL;
    
    struct Node **queue = (struct Node**)malloc(sizeof(struct Node *) * 5000);
    int head = 0;
    int tail = 0;
    queue[tail++] = root;

    while (head != tail) {
        int size = tail - head;
        for (int i = 0; i < size; i++) {
            struct Node *temp = queue[head++];
            if (i < size - 1) temp->next = queue[head];
            if (temp->left) queue[tail++] = temp->left;
            if (temp->right) queue[tail++] = temp->right;
        }
    }

    return root;
}