#include <bits/stdc++.h>


// #define KMP_START_POSITION 0 // 从str[0]开始向后读len个字符，从next[0]开始写入
#define KMP_START_POSITION 1 // 从str[1]开始向后读len个字符，从next[1]开始写入

const long long int STRING_LENGTH_MAX = 1e6;
char str[STRING_LENGTH_MAX + 2], pattern[STRING_LENGTH_MAX + 2];
int next[STRING_LENGTH_MAX + 1];
 
#if KMP_START_POSITION == 0
template<typename CharType> void kmp_next_init(const CharType *str, int len, int *next) {
    int j = 0;
    next[0] = 0;
    for(int i = 1; i < len; ++i) {
        while(j > 0 && str[i] != str[j]) { j = next[j - 1]; }
        if(str[i] == str[j]) { ++j; }
        next[i] = j;
    }
}
int kmp_find_first(const char *str, const char *pattern, const int str_len, const int pattern_len, const int *next) {
    int i = 0, j = 0;
    while(i < str_len) {
        if(str[i] == pattern[j]) {
            ++i; ++j;
            if(j == pattern_len) {
                return i - j; // 或改成std::cout后继续后续识别
            }
        } else if(j > 0) {
            j = next[j - 1];
        } else {
            ++i;
        }
    }
    return -1;
}
#elif KMP_START_POSITION == 1
/* 未经优化的版本
template<typename CharType> void kmp_next_init(const CharType *str, int len, int *next) {
    assert(str[0] == '\0'); // 确保str从str[1]开始记录
    next[0] = 0;
    next[1] = 0;
    int j = 0;
    for(int i = 2; i <= len; ++i) {
        while(j > 0 && str[i] != str[j + 1]) { j = next[j]; }
        if(str[i] == str[j + 1]) { ++j; }
        next[i] = j;
    }
}
*/
template<typename CharType> void kmp_next_init(const CharType *str, int len, int *next) {
    assert(str[0] == '\0'); // 确保str从str[1]开始记录
    next[0] = -1;
    next[1] = 0;
    for(int i = 2, j = next[1]; i <= len; ++i) {
        while(j != -1 && str[i] != str[j + 1]) { j = next[j]; }
        next[i] = ++j;
    }
}
template<typename CharType> int kmp_find_first(const CharType *str, const CharType *pattern, const int str_len, const int pattern_len, const int *next) {
    for(int i = 1, j = 0; i <= str_len; ++i) {
        while(j > 0 && str[i] != pattern[j + 1]) { j = next[j]; }
        if(str[i] == pattern[j + 1]) { ++j; }
        if(j == pattern_len) {
            std::cout << i - j + 1; // 或改成std::cout后继续后续识别
        }
    }
    return -1;
}
#endif