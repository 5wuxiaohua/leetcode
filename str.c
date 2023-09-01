#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

// https://leetcode.cn/problems/reverse-string/
// 反转字符串
void swap(char *a, char *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void reverseString(char* s, int sSize) {
    int i = 0;
    int j = sSize - 1;
    
    while (i < j) {
        swap(&(s[i]), &(s[j]));
        i++;
        j--;
    }
}

// https://leetcode.cn/problems/reverse-words-in-a-string/
// 反转字符串中的单词
void reverse(char *s, int start, int end) {
    while (start < end) {
        swap(&s[start++], &s[end--]);
    }
}

void removeSpace(char *s) {
    int start = 0;
    int end = strlen(s) - 1;
    while (s[start] == ' ') start++;
    while (s[end] == ' ') end--;

    int slow = 0;
    for (int i = start; i <= end; i++) {
        if (s[i] == ' ' && s[i + 1] == ' ') continue;
        s[slow++] = s[i];
    }
    s[slow] = '\0';
}

char *reverseWords(char *s){
    removeSpace(s);
    reverse(s, 0, strlen(s) - 1);

    int slow = 0;
    for (int i = 0; i <= strlen(s); i++) {
        if (s[i] == ' ' || s[i] == '\0') {
            reverse(s, slow, i - 1);
            slow = i + 1;
        }
    }
    return s;
}