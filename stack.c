#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// getMin 功能栈，时间复杂度为O(1)
typedef struct MyStack {
    int stackData[100];
    int stackMin[100];
} myStack;

int stackDataTop = 0;
int stackMinTop = 0;
myStack stack = {0};

void push(int data) {
    stack.stackData[stackDataTop++] = data;
    if (stackMinTop == 0) {
        stack.stackMin[stackMinTop++] = data;
    }
    if (data <= stack.stackMin[stackMinTop - 1]) {
        stack.stackMin[stackMinTop++] = data;
    }
}

int pop() {
    if (stack.stackData[stackDataTop - 1] = stack.stackMin[stackMinTop - 1]) {
        stackMinTop--;
    }
    return stack.stackData[stackDataTop--];
}

int getMin() {
    return stack.stackMin[stackMinTop - 1];
}

// 用一个栈实现另一个栈的排序(栈顶到栈底从小到大排序)
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
}

// https://leetcode.cn/problems/implement-queue-using-stacks/
// 用栈实现队列
typedef struct {
    int stackInTop;
    int stackOutTop;
    int stackIn[100];
    int stackOut[100];
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue *queue = (MyQueue *)malloc(sizeof(MyQueue));
    queue->stackInTop = 0;
    queue->stackOutTop = 0;
    return queue;
}

void myQueuePush(MyQueue* obj, int x) {
    obj->stackIn[obj->stackInTop++] = x;
}

int myQueuePop(MyQueue* obj) {
    while (obj->stackInTop) {
        obj->stackOut[obj->stackOutTop++] = obj->stackIn[--obj->stackInTop];
    }
    int data = obj->stackOut[--obj->stackOutTop];

    while (obj->stackOutTop) {
        obj->stackIn[obj->stackInTop++] = obj->stackOut[--obj->stackOutTop];
    }

    return data;
}

int myQueuePeek(MyQueue* obj) {
    return obj->stackIn[0];
}

bool myQueueEmpty(MyQueue* obj) {
    return obj->stackInTop == 0;
}

void myQueueFree(MyQueue* obj) {
    obj->stackInTop = 0;
    obj->stackOutTop = 0;

}

// https://leetcode.cn/problems/implement-stack-using-queues/
// 用队列实现栈
typedef struct {
    int head;
    int rear;
    int queue[100];
} MyStack;


MyStack* myStackCreate() {
    MyStack *stack = (MyStack *)malloc(sizeof(MyStack));
    stack->head = 0;
    stack->rear = 0;
    return stack;
}

void myStackPush(MyStack* obj, int x) {
    obj->queue[obj->rear++] = x;
}

int myStackPop(MyStack* obj) {
    return obj->queue[--obj->rear];
}

int myStackTop(MyStack* obj) {
    return obj->queue[obj->rear - 1];
}

bool myStackEmpty(MyStack* obj) {
    return obj->head == obj->rear;
}

void myStackFree(MyStack* obj) {
    obj->head = 0;
    obj->rear = 0;
}

// https://leetcode.cn/problems/valid-parentheses/
// 有效的括号
bool isValid(char *s){
    char stack[10000] = {0};
    int top = 0;
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack[top++] = s[i];
        } else {
            if (top == 0) return;
            switch(s[i]) {
                case ')' : 
                    if (stack[--top] != '(') {
                        return false;
                    } else {
                        break;
                    }
                case ']' : 
                    if (stack[--top] != '[') {
                        return false;
                    } else {
                        break;
                    }
                case '}' : 
                    if (stack[--top] != '{') {
                        return false;
                    } else {
                        break;
                    }
                }
        }
    }
    
    return top == 0 ? true : false;
}

// https://leetcode.cn/problems/evaluate-reverse-polish-notation/
// 逆波兰表达式求值
bool isNumber(char* token) {
    return strlen(token) > 1 || ('0' <= token[0] && token[0] <= '9');
}

int evalRPN(char** tokens, int tokensSize) {
    int *stk = (int *)malloc(sizeof(int) * tokensSize); 
    int top = 0;
    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];
        if (isNumber(token)) {
            stk[top++] = atoi(token);
        } else {
            int num2 = stk[--top];
            int num1 = stk[--top];
            switch (token[0]) {
                case '+':
                    stk[top++] = num1 + num2;
                    break;
                case '-':
                    stk[top++] = num1 - num2;
                    break;
                case '*':
                    stk[top++] = num1 * num2;
                    break;
                case '/':
                    stk[top++] = num1 / num2;
                    break;
            }
        }
    }
    return stk[top - 1];
}