#include <bits/stdc++.h>

/**
 * 快速幂
 */
inline long long int fast_power(long long int base, long long int power) {
    long long int result = 1;
    while(power > 0) {
        if(power % 2) { result *= base; }
        base = base * base;
        power /= 2;
    }
    return result;
}

/**
 * 带有取模的快速幂
 */
inline long long int fast_power(long long int base, long long int power, long long int mod) {
    long long int result = 1;
    base %= mod;
    while(power > 0) {
        if(power % 2) { result = (result * base) % mod; }
        base = (base * base) % mod;
        power /= 2;
    }
    return result;
}