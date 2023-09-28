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


// https://leetcode.cn/problems/min-cost-to-connect-all-points/description/
// 连接所有点的最小费用
void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b, *b = tmp;
}

struct Edge {
    int len, x, y;
};

int cmp(struct Edge* a, struct Edge* b) {
    return a->len - b->len;
}

int find(int* f, int x) {
    return f[x] == x ? x : (f[x] = find(f, f[x]));
}

int unionSet(int* f, int* rank, int x, int y) {
    int fx = find(f, x), fy = find(f, y);
    if (fx == fy) {
        return false;
    }
    if (rank[fx] < rank[fy]) {
        swap(&fx, &fy);
    }
    rank[fx] += rank[fy];
    f[fy] = fx;
    return true;
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize) {
    int n = pointsSize;
    struct Edge edges[(n + 1) * n / 2];
    int edgesSize = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges[edgesSize].x = i;
            edges[edgesSize].y = j;
            edges[edgesSize++].len = fabs(points[i][0] - points[j][0]) + fabs(points[i][1] - points[j][1]);
        }
    }
    qsort(edges, edgesSize, sizeof(struct Edge), cmp);
    int f[n], rank[n];
    for (int i = 0; i < n; i++) {
        f[i] = i;
        rank[i] = 1;
    }
    int ret = 0;
    for (int i = 0; i < edgesSize; i++) {
        if (unionSet(f, rank, edges[i].x, edges[i].y)) {
            ret += edges[i].len;
        }
    }
    return ret;
}

// 二叉树的递归遍历
typedef struct TreeNode TreeNode;
void preOrder(TreeNode *root) {
    if (root == NULL) return;
    int stack[10000] = {0};
    int top = 0;
    stack[top++] = root->val;
    preOrder(root->left);
    preOrder(root->right);
}

// 二叉树的迭代遍历
void preOrder(TreeNode *root) {
    TreeNode *stack[100] = {0};
    int top = 0;
    stack[top++] = root;
    TreeNode *cur = root;
    while (top >= 0) {
        cur = stack[--top];
        printf("%d ", cur->val);
        if (cur->right) {
            stack[top++] = cur->right;
        }
        if (cur->left) {
            stack[top++] = cur->left;
        }
    }

}

void inOrder(TreeNode *root) {
    TreeNode *stack[100] = {0};
    int top = 0;
    stack[top++] = root;
    TreeNode *cur = root;
    while (cur != NULL && top >= 0) {
        if (cur->left) {
            stack[top++] = cur->left;
            cur = cur->left;
        } else {
            cur = stack[--top];
            printf("%d ", cur->val);
            cur = cur->right;
        }
    }
}

void bfsTree(TreeNode *root) {
    TreeNode *heap[100] = {0};
    int head = 0;
    int tail = 0;
    heap[tail++] = root;
    while (tail != head) {
        TreeNode *cur = heap[head++];
        printf("%d ", cur->val);
        if (cur->left) heap[tail++] = cur->left;
        if (cur->right) heap[tail++] = cur->right;
    }
}

// https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
// 102. 二叉树的层序遍历
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int **ans = (int **)malloc(sizeof(int *) * 2000);
    int retSize = 0;
    int *path = (int *)malloc(sizeof(int) * 2000);
    int pathSize = 0;
    int *retColSize = (int *)malloc(sizeof(int) * 2000);

    TreeNode *heap[2000] = {0};
    int head = 0;
    int tail = 0;

    heap[tail++] = root;
    while (head != tail) {
        int size = tail - head;
        for (int i = 0; i < size; i++) {
            TreeNode *temp = heap[head++];
            path[pathSize++] = temp->val;
            if (temp->left) heap[tail++] = temp->left;
            if (temp->right) heap[tail++] = temp->right;
        }

        int *temp = (int *)malloc(sizeof(int) * pathSize);
        memcpy(temp, path, sizeof(int) * pathSize);
        ans[retSize] = temp;
        retColSize[retSize++] = pathSize;
        pathSize = 0;
    }

    *returnSize = retSize;
    *returnColumnSizes = retColSize;

    return ans;
}

// https://leetcode.cn/problems/binary-tree-level-order-traversal-ii/description/
// 107. 二叉树的层序遍历 II
int** levelOrderBottom(struct TreeNode* root, int* returnSize, int** returnColumnSizes){
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int **ans = (int **)malloc(sizeof(int *) * 2000);
    int retSize = 0;
    int *path = (int *)malloc(sizeof(int) * 2000);
    int pathSize = 0;
    int *retColSize = (int *)malloc(sizeof(int) * 2000);

    TreeNode *heap[2000] = {0};
    int head = 0;
    int tail = 0;

    heap[tail++] = root;
    while (head != tail) {
        int size = tail - head;
        for (int i = 0; i < size; i++) {
            TreeNode *temp = heap[head++];
            path[pathSize++] = temp->val;
            if (temp->left) heap[tail++] = temp->left;
            if (temp->right) heap[tail++] = temp->right;
        }

        int *temp = (int *)malloc(sizeof(int) * pathSize);
        memcpy(temp, path, sizeof(int) * pathSize);
        ans[retSize] = temp;
        retColSize[retSize++] = pathSize;
        pathSize = 0;
    }


    int **ans1 = (int **)malloc(sizeof(int *) * retSize);
    int *retColSize1 = (int *)malloc(sizeof(int *) * retSize);

    int j = 0;
    for (int i = retSize - 1; i >= 0; i--) {
        ans1[j] = ans[i];
        retColSize1[j++] = retColSize[i];
    }

    *returnSize = retSize;
    *returnColumnSizes = retColSize1;

    return ans1;
}