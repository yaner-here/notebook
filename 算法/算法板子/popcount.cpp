#include<cstdint>

/* 原始版本，时间复杂度O(log n) */
template<typename T> static inline T popcount(T x) {
    T ans = 0;
    while(x > 0) {
        ans += x & 1;
        x >>= 1;
    }
    return ans;
}
int popcount(uint64_t x) {
    int res;
    for(res = 0; x > 0; x -= x & -x) { ++res; }
    return res;
}

/* lowbit加速版本，时间复杂度O(popcount(n)) */
unsigned int CountOne5(unsigned int x) {
    unsigned int tmp = x - ((x >> 1) & 033333333333) - ((x >> 2) & 011111111111);
    return ((tmp + (tmp >> 3)) & 030707070707) % 63;
}

/* O3优化版本，时间复杂度O(1) */
static inline uint32_t popcount(uint32_t x) {
    x = (x & 0x55555555u) + ((x >> 1) & 0x55555555u);
    x = (x & 0x33333333u) + ((x >> 2) & 0x33333333u);
    x = (x & 0x0F0F0F0Fu) + ((x >> 4) & 0x0F0F0F0Fu);
    x = (x & 0x00FF00FFu) + ((x >> 8) & 0x00FF00FFu);
    x = (x & 0x0000FFFFu) + ((x >> 16) & 0x0000FFFFu);
    return x;
}
static inline uint64_t popcount(uint64_t x) {
    constexpr uint64_t m1 = 0x5555555555555555ull;
    constexpr uint64_t m2 = 0x3333333333333333ull;
    constexpr uint64_t m4 = 0x0F0F0F0F0F0F0F0Full;
    constexpr uint64_t h01 = 0x0101010101010101ull;
    x -= (x >> 1) & m1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    return (x * h01) >> 56;
}