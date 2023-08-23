#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int value;
   struct node *left;
   struct node *right;
} node;

node *createNode(int data) {
    node *new = (node *)malloc(sizeof(node));
    new->value = data;
    new->left = new->right = NULL;
    return new;
}

void buildTree(node **root, int *nums, int len, int i) {
    if (i > len - 1 || nums[i] == -1) {
        return;
    }

    *root = createNode(nums[i]);
    buildTree(&((*root)->left), nums, len, 2*i + 1);
    buildTree(&((*root)->right), nums, len, 2*i + 2);
}

int stack[100] = {0};
int top = 0;
void preOrder(node *root) {
   if (root == NULL) return;

   stack[top++] = root->value;
   preOrder(root->left);
   preOrder(root->right);
}

void printTree() {
    for (int i = 0; i < top; i++) {
        printf("%d\n", stack[i]);
    }
}

int main() {
    int array[5] = {1,2,3,4,5};
    node *root = NULL;
    buildTree(&root, array, sizeof(array)/sizeof(int), 0);
    preOrder(root);
    printTree();
    return 0;
}