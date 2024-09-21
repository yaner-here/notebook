#include <bits/stdc++.h>
#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <iomanip>

#define ceil1(x) ((x) > (int) (x) ? (int) (x) + 1 : (int) (x))
#define ceil2(x) ((x + 0.5))
#define max_macro(x, y) ((x) > (y) ? (x) : (y))
#define min_macro(x, y) ((x) > (y) ? (y) : (x))
inline bool is_squared(long long int x) { return ((x - 1) & x) == 0; }
template<typename T> T multi_max(std::initializer_list<T> list) { return *std::max_element(list.begin(), list.end()); }
template<typename T> T multi_min(std::initializer_list<T> list) { return *std::min_element(list.begin(), list.end()); }
/**
 * 返回输入正数的回文数
 */
inline long long int palindrome(long long int x) {
    long long int ans = 0;
    while(x > 0) {
        ans = ans * 10 + x % 10;
        x /= 10;
    }
    return ans;
}

/**
 * 十进制数字转任意进制字符串
 */
inline std::string convertToBase(long long int x, long long int base) {
    if(x == 0) { return "0"; }
    std::string result;
    while(x > 0) {
        if(x % base <= 9) {
            result += x % base + '0';
        } else if(x % base <= 35) {
            result += x % base - 10 + 'A';
        }
        x /= base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

/**
 * 任意进制字符串转十进制数字
 */
inline long long int convertFromBase(std::string x, long long int base) {
    long long int result = 0;
    for(size_t i = 0; i < x.size(); ++i) {
        if(x[i] <= 'Z' && x[i] >= 'A') {
            result = result * base + x[i] - 'A' + 10;
            continue;
        } else if(x[i] <= 'z' && x[i] >= 'a') {
            result = result * base + x[i] - 'a' + 10;
            continue;
        }
        result = result * base + x[i] - '0';
    }
    return result;
}

/**
 *  辗转相除法求最大公约数
 */
long long int gcd(long long int a, long long int b) { return b == 0 ? a : gcd(b, a % b); }

/**
 *  辗转相除法求最小公倍数
 */
long long int lcm(long long int a, long long int b) { return (a * b) / gcd(a, b); }

inline bool is_in_open_range(long long int x, long long int y, long long int n, long long int m) { return x >= 0 && x < n && y >= 0 && y < m; }
inline bool is_in_closed_range(long long int x, long long int y, long long int n, long long int m) { return x >= 1 && x <= n && y >= 1 && y <= m; }

unsigned int popcount(unsigned int u) {
    u = (u & 0x55555555) + ((u >> 1) & 0x55555555);
    u = (u & 0x33333333) + ((u >> 2) & 0x33333333);
    u = (u & 0x0F0F0F0F) + ((u >> 4) & 0x0F0F0F0F);
    u = (u & 0x00FF00FF) + ((u >> 8) & 0x00FF00FF);
    u = (u & 0x0000FFFF) + ((u >> 16) & 0x0000FFFF);
    return u;
}

unsigned long long int get_hash(const char *str, int stride = 1) {
    unsigned long long int hash = 0;
    while(*str != '\0') {
        hash = hash * 131 + *str;
        str += stride;
    }
    return hash;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
}