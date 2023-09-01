#include <stdio.h>
#include <stdbool.h>

bool strstr(char *p, char *s) {
    for (int i = 0; i < strlen(p); i++) {
        for (int j = 0; j < strlen(s); j++) {
            if (s[j] != p[i + j]) {
                break;
            }
            return true;
        }
    }

    return false;
}

// KMP
void getNext(char *s, int *next) {
    int j = 0;
    next[0] = 0;

    for (int i = 1; i < strlen(s); i++) {
        while (j >0 && s[i] != s[j]) {
            j = next[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        next[i] = j;
    }
}

int strstr(char *str, char *pattern) {
    int *next = (int *)malloc(sizeof(int) * strlen(pattern));
    getNext(pattern, next);

    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        while (j > 0 && str[i] != pattern[j]) {
            j = next[j - 1];
        }
        if (str[i] == pattern[j]) {
            j++;
        }
        if (j == strlen(pattern)) {
            return i - strlen(pattern) + 1;
        }
    }
    return -1;
}