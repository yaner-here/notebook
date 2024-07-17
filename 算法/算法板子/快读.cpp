#include<bits/stdc++.h>

inline long long int fast_read() {
    long long int x = 0;
    bool symbol = true;
    char character = getchar();
    while(character < '0' || character > '9') {
        if(character == '-') { symbol = !symbol; }
        character = getchar();
    }
    while(character >= '0' && character <= '9') {
        x = (x << 3) + (x << 1) + (character - '0');
        character = getchar();
    }
    return symbol ? x : -x;
}
inline void fast_read(long long int &x) { x = fast_read(); }
