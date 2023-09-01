#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ListNode {
    int val;
    struct ListNode *next;
} ;

// https://leetcode.cn/problems/remove-linked-list-elements/
// 移除链表元素
struct ListNode* removeElements(struct ListNode* head, int val){
    while (head && head->val == val) {
        head = head->next;
    }

    struct ListNode *cur = head;
    while (cur && (cur->next)) {
        if (cur->next->val == val) {
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }

    return head;
}

// 使用虚拟头结点
struct ListNode* removeElements(struct ListNode* head, int val){ 
    struct ListNode *shead = (struct ListNode *)malloc(sizeof(struct ListNode));
    shead->next = head;

    struct ListNode *cur = shead;
    while (cur->next) {
        if (cur->next->val == val) {
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
    head = shead->next;
    return head;   
}

// https://leetcode.cn/problems/design-linked-list/
// 设计链表 
typedef struct MyLinkList{
    int value;
    struct MyLinkList *next;
} MyLinkedList;


MyLinkedList* myLinkedListCreate() {
    MyLinkedList *head = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    head->next = NULL;
    return head;
}

int myLinkedListGet(MyLinkedList* obj, int index) {
    int num = 0;
    MyLinkedList *cur = obj->next;
    while (cur) {
        if (num == index) {
            return cur->value;
        }
        cur = cur->next;
        num++;
    }
    return -1;
}

void myLinkedListAddAtHead(MyLinkedList* obj, int val) {
    MyLinkedList *head = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    head->value = val;
    head->next = obj->next;
    obj->next = head;
}

void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
    while (obj->next) {
        obj = obj->next;
    }

    MyLinkedList *newNode = (MyLinkedList *)malloc(sizeof(MyLinkedList));
    obj->next = newNode;
    newNode->value = val;
    newNode->next = NULL;
}

void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
    MyLinkedList *cur = obj;
    int num = 0;
    while (cur) {
        if (num == index) {
            MyLinkedList *newNode = (MyLinkedList *)malloc(sizeof(MyLinkedList));
            newNode->value = val;
            newNode->next = cur->next;
            cur->next = newNode;
            return;
        }
        cur = cur->next;
        num++;
    }
}

void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
    MyLinkedList *cur = obj;
    int num = 0;
    while (cur) {
        if (num == index) {
            if (cur->next == NULL) {
                return;
            } 
            cur->next = cur->next->next;
            return;
        }
        cur = cur->next;
        num++;
    }

}

void myLinkedListFree(MyLinkedList* obj) {
    while (obj) {
        MyLinkedList *temp = obj;
        obj = obj->next;
        free(temp);
    }
}

// https://leetcode.cn/problems/reverse-linked-list/
// 翻转链表
struct ListNode* reverseList(struct ListNode* head){
    if (head == NULL) return NULL;
    struct ListNode *cur = head;
    struct ListNode *pre = NULL;

    while (cur) {
        struct ListNode *temp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = temp;
    }
    return pre;
}

// 递归法翻转链表
struct ListNode *iterate(struct ListNode *pre, struct ListNode *cur) {
    if (cur == NULL) return pre; 

    struct ListNode *temp = cur->next;
    cur->next = pre;
    return iterate(cur, temp);
}
struct ListNode* reverseList(struct ListNode* head){ 
    if (head == NULL) return NULL;

    return iterate(NULL, head);
}


// https://leetcode.cn/problems/swap-nodes-in-pairs/
// 两两交换链表中的节点
struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) return head;

    typedef struct ListNode ListNode;
    ListNode *dummyHead = (ListNode *)malloc(sizeof(ListNode));
    dummyHead->next = head;
    ListNode *cur = dummyHead;
    while (cur->next != NULL && cur->next->next != NULL) {
        ListNode *temp = cur->next;
        ListNode *temp1 = cur->next->next;

        cur->next = cur->next->next;
        cur->next->next = temp;
        temp->next = temp1;

        cur = cur->next->next;

    }

    return dummyHead->next;
}

// https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
// 删除链表的倒数第 N 个结点
struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    typedef struct ListNode ListNode;
    ListNode *dummyHead = (ListNode *)malloc(sizeof(ListNode));
    dummyHead->next = head;
    struct ListNode *fast = dummyHead;
    struct ListNode *slow = dummyHead;

    while (n > 0) {
        fast = fast->next;
        n--;
    }
    while (fast->next) {    //  判断fast->next，否则多走一步
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = slow->next->next;
    head = dummyHead->next;
    free(dummyHead);
    return head;
}

// https://leetcode.cn/problems/intersection-of-two-linked-lists-lcci/
// 链表相交
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    typedef struct ListNode ListNode;
    if (headA == NULL || headB == NULL) return NULL;

    ListNode *curA = headA;
    ListNode *curB = headB;
    int lenA = 0;
    int lenB = 0;
    while (curA) {
        lenA++;
        curA = curA->next; 
    }

    while (curB) {
        lenB++;
        curB = curB->next;
    }

    if (lenA < lenB) {
        curA = headB;
        curB = headA;        
    } else {
        curA = headA;
        curB = headB;
    }

    int len = fabs(lenA - lenB);
    while (len--) {
        curA = curA->next;
    }

    while (curA) {
        if (curA == curB) {
            return curA;
        }
        curA = curA->next;
        curB = curB->next;
    }    

    return NULL;
}