#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printPMT(const char *pattern, int *next, int len) {
    printf("------Partial Match Table--------\n");
    for (int i = 0; i < len; i++) {
        printf("%c ", pattern[i]);
    }
    printf("\n");

    for (int i = 0; i < len; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");
    printf("----------------------------------\n");
}

void next(const char *pattern, int *next, int len) {
    for (int i = 0; i < len; i++) {
        next[i] = 0;
        for (int preIndex = i; preIndex > 0;) {
            if (pattern[next[preIndex - 1]] == pattern[i]) {
                next[i] = next[preIndex - 1] + 1;
                break;
            }
            preIndex = next[preIndex - 1];
        }
    }

    printPMT(pattern, next, len);
}

int kmp_match(const char *str, const char *pattern) {
    if (str == NULL || *str == 0 || pattern == NULL || *pattern == 0) {
        return -1;
    }
    
    int lenOfPattern = strlen(pattern);
    int *nextTbl = (int *)malloc(lenOfPattern * sizeof(int));
    if (nextTbl == NULL) {
        return -1;
    }
    memset(nextTbl, 0, lenOfPattern * sizeof(int));
    next(pattern, nextTbl, lenOfPattern);

    int matchIndexOfMainString = 0;
    int matchStartIndexOfMainString = 0;
    int matchIndexOfPatternString = 0;
    int lenOfMainString = strlen(str);
    while (true) {  
        for (; matchIndexOfMainString < lenOfMainString && matchIndexOfPatternString < lenOfPattern; matchIndexOfMainString++, matchIndexOfPatternString++) {
            if (str[matchIndexOfMainString] != pattern[matchIndexOfPatternString]) {
                break;
            }
        }

        if (matchIndexOfPatternString == lenOfPattern) {
            free(nextTbl);
            return matchStartIndexOfMainString;
        }

        if (matchIndexOfMainString == lenOfMainString) {
            free(nextTbl);
            return -1;
        }
        
        if (matchIndexOfPatternString == 0) {
            matchStartIndexOfMainString += 1;
            matchIndexOfMainString = matchStartIndexOfMainString;
        } else {
            matchStartIndexOfMainString += matchIndexOfPatternString - nextTbl[matchIndexOfPatternString - 1];
            matchIndexOfPatternString = nextTbl[matchIndexOfPatternString - 1];
        }

    }
    free(nextTbl);

    return -1;
}

char *myStrstr(char *str, char *pattern) {
    int pos = kmp_match(str, pattern);
    if (pos >= 0) {
        return &str[pos];
    }
    return NULL;
}

int main(int argc, char **argv) {
    const char *str = "aaaaabaa";
    const char *pattern = "aabaa";
    int pos = kmp_match(str, pattern);
    if (pos >= 0) {
        printf("Find %s from %s at pos %d\n", pattern, str, pos);
    } else {
        printf("Match failed!\n");
    }

    return 0;
}
