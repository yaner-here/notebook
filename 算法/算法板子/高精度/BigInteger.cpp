/**
 * https://www.luogu.com.cn/article/rz9ubds1
 * 要求C++20
 */

#include <bits/stdc++.h>

namespace __FFT {
    constexpr int64_t FFT_BASE = 1e4;
    constexpr double PI2 = 6.283185307179586231995927;
    constexpr double PI6 = 18.84955592153875869598778;
    constexpr int RECALC_WIDTH = 10;
    constexpr int RECALC_BASE = (1 << RECALC_WIDTH) - 1;
    struct complex {
        double real, imag;
        complex(double x = 0.0, double y = 0.0): real(x), imag(y) {}
        complex operator+(const complex &other) const { return complex(real + other.real, imag + other.imag); }
        complex operator-(const complex &other) const { return complex(real - other.real, imag - other.imag); }
        complex operator*(const complex &other) const { return complex(real * other.real - imag * other.imag, real * other.imag + other.real * imag); }
        complex &operator+=(const complex &other) { return real += other.real, imag += other.imag, *this; }
        complex &operator-=(const complex &other) { return real -= other.real, imag -= other.imag, *this; }
        complex &operator*=(const complex &other) { return *this = *this * other; }
    };
    complex *arr = nullptr;
    inline void init(int n) {
        if(arr != nullptr) delete[] arr, arr = nullptr;
        arr = new complex[n + 1];
    }
    template<const int n> inline void fft(complex *a) {
        const int n2 = n >> 1, n4 = n >> 2;
        complex w(1.0, 0.0), w3(1.0, 0.0);
        const complex wn(std::cos(PI2 / n), std::sin(PI2 / n)), wn3(std::cos(PI6 / n), std::sin(PI6 / n));
        for(int i = 0; i < n4; i++, w *= wn, w3 *= wn3) {
            if(!(i & RECALC_BASE)) w = complex(std::cos(PI2 * i / n), std::sin(PI2 * i / n)), w3 = w * w * w;
            complex x = a[i] - a[i + n2], y = a[i + n4] - a[i + n2 + n4];
            y = complex(y.imag, -y.real);
            a[i] += a[i + n2], a[i + n4] += a[i + n2 + n4];
            a[i + n2] = (x - y) * w, a[i + n2 + n4] = (x + y) * w3;
        }
        fft<n2>(a), fft<n4>(a + n2), fft<n4>(a + n2 + n4);
    }
    template<> inline void fft<0>(complex *) {}
    template<> inline void fft<1>(complex *) {}
    template<> inline void fft<2>(complex *a) {
        complex x = a[0], y = a[1];
        a[0] += y, a[1] = x - y;
    }
    template<> inline void fft<4>(complex *a) {
        complex a0 = a[0], a1 = a[1], a2 = a[2], a3 = a[3];
        complex x = a0 - a2, y = a1 - a3;
        y = complex(y.imag, -y.real);
        a[0] += a2, a[1] += a3, a[2] = x - y, a[3] = x + y;
        fft<2>(a);
    }
    template<const int n> inline void ifft(complex *a) {
        const int n2 = n >> 1, n4 = n >> 2;
        ifft<n2>(a), ifft<n4>(a + n2), ifft<n4>(a + n2 + n4);
        complex w(1.0, 0.0), w3(1.0, 0.0);
        const complex wn(std::cos(PI2 / n), -std::sin(PI2 / n)), wn3(std::cos(PI6 / n), -std::sin(PI6 / n));
        for(int i = 0; i < n4; i++, w *= wn, w3 *= wn3) {
            if(!(i & RECALC_BASE)) w = complex(std::cos(PI2 * i / n), -std::sin(PI2 * i / n)), w3 = w * w * w;
            complex p = w * a[i + n2], q = w3 * a[i + n2 + n4];
            complex x = a[i], y = p + q, x1 = a[i + n4], y1 = p - q;
            y1 = complex(y1.imag, -y1.real);
            a[i] += y, a[i + n4] += y1, a[i + n2] = x - y, a[i + n2 + n4] = x1 - y1;
        }
    }
    template<> inline void ifft<0>(complex *) {}
    template<> inline void ifft<1>(complex *) {}
    template<> inline void ifft<2>(complex *a) {
        complex x = a[0], y = a[1];
        a[0] += y, a[1] = x - y;
    }
    template<> inline void ifft<4>(complex *a) {
        ifft<2>(a);
        complex p = a[2], q = a[3];
        complex x = a[0], y = p + q, x1 = a[1], y1 = p - q;
        y1 = complex(y1.imag, -y1.real);
        a[0] += y, a[1] += y1, a[2] = x - y, a[3] = x1 - y1;
    }
    inline void dft(complex *a, int n) {
        if(n <= 1) return;
        switch(n) {
        case 1 << 2: fft<1 << 2>(a); break;
        case 1 << 3: fft<1 << 3>(a); break;
        case 1 << 4: fft<1 << 4>(a); break;
        case 1 << 5: fft<1 << 5>(a); break;
        case 1 << 6: fft<1 << 6>(a); break;
        case 1 << 7: fft<1 << 7>(a); break;
        case 1 << 8: fft<1 << 8>(a); break;
        case 1 << 9: fft<1 << 9>(a); break;
        case 1 << 10: fft<1 << 10>(a); break;
        case 1 << 11: fft<1 << 11>(a); break;
        case 1 << 12: fft<1 << 12>(a); break;
        case 1 << 13: fft<1 << 13>(a); break;
        case 1 << 14: fft<1 << 14>(a); break;
        case 1 << 15: fft<1 << 15>(a); break;
        case 1 << 16: fft<1 << 16>(a); break;
        case 1 << 17: fft<1 << 17>(a); break;
        case 1 << 18: fft<1 << 18>(a); break;
        case 1 << 19: fft<1 << 19>(a); break;
        case 1 << 20: fft<1 << 20>(a); break;
        case 1 << 21: fft<1 << 21>(a); break;
        case 1 << 22: fft<1 << 22>(a); break;
        case 1 << 23: fft<1 << 23>(a); break;
        case 1 << 24: fft<1 << 24>(a); break;
        case 1 << 25: fft<1 << 25>(a); break;
        case 1 << 26: fft<1 << 26>(a); break;
        case 1 << 27: fft<1 << 27>(a); break;
        case 1 << 28:
            fft<1 << 28>(a);
            break;
            std::cerr << "FFTLimitExceededError" << '\n'; exit(-1);
        }
    }
    inline void idft(complex *a, int n) {
        if(n <= 1) return;
        switch(n) {
        case 1 << 2: ifft<1 << 2>(a); break;
        case 1 << 3: ifft<1 << 3>(a); break;
        case 1 << 4: ifft<1 << 4>(a); break;
        case 1 << 5: ifft<1 << 5>(a); break;
        case 1 << 6: ifft<1 << 6>(a); break;
        case 1 << 7: ifft<1 << 7>(a); break;
        case 1 << 8: ifft<1 << 8>(a); break;
        case 1 << 9: ifft<1 << 9>(a); break;
        case 1 << 10: ifft<1 << 10>(a); break;
        case 1 << 11: ifft<1 << 11>(a); break;
        case 1 << 12: ifft<1 << 12>(a); break;
        case 1 << 13: ifft<1 << 13>(a); break;
        case 1 << 14: ifft<1 << 14>(a); break;
        case 1 << 15: ifft<1 << 15>(a); break;
        case 1 << 16: ifft<1 << 16>(a); break;
        case 1 << 17: ifft<1 << 17>(a); break;
        case 1 << 18: ifft<1 << 18>(a); break;
        case 1 << 19: ifft<1 << 19>(a); break;
        case 1 << 20: ifft<1 << 20>(a); break;
        case 1 << 21: ifft<1 << 21>(a); break;
        case 1 << 22: ifft<1 << 22>(a); break;
        case 1 << 23: ifft<1 << 23>(a); break;
        case 1 << 24: ifft<1 << 24>(a); break;
        case 1 << 25: ifft<1 << 25>(a); break;
        case 1 << 26: ifft<1 << 26>(a); break;
        case 1 << 27: ifft<1 << 27>(a); break;
        case 1 << 28:
            ifft<1 << 28>(a);
            break;
            std::cerr << "FFTLimitExceededError" << '\n'; exit(-1);
        }
    }
}
class BigInteger {
  protected:
    using digit_t = int64_t;
    static constexpr int WIDTH = 8;
    static constexpr digit_t BASE = 1e8;
    static constexpr int64_t FFT_LIMIT = 32;
    static constexpr int64_t NEWTON_DIV_LIMIT = 64;
    static constexpr int64_t NEWTON_DIV_MIN_LEVEL = 16;
    static constexpr int64_t NEWTON_SQRT_LIMIT = 48;
    static constexpr int64_t NEWTON_SQRT_MIN_LEVEL = 5;
    digit_t *digits;
    int capacity, size;
    bool flag;
    inline void push(const digit_t &val) {
        if(size == capacity) {
            int new_capacity = 0;
            if(capacity < 256) new_capacity = capacity << 1;
            else new_capacity = std::pow(capacity + 1, 0.125) * capacity;
            digit_t *new_digits = new digit_t[new_capacity + 1];
            std::memcpy(new_digits, digits, sizeof(int64_t) * (capacity + 1));
            delete[] digits;
            digits = new_digits, capacity = new_capacity;
        }
        digits[++size] = val;
    }
    inline void pop() { digits[size--] = 0; }
    inline int compare(const BigInteger &x) const {
        if(flag && !x.flag) return 1;
        if(!flag && x.flag) return -1;
        int sgn = (flag && x.flag ? 1 : -1);
        if(size > x.size) return sgn;
        if(size < x.size) return -sgn;
        for(int i = size; i >= 1; i--) {
            if(digits[i] > x.digits[i]) return sgn;
            if(digits[i] < x.digits[i]) return -sgn;
        }
        return 0;
    }
    static BigInteger fft_mul(const BigInteger &a, const BigInteger &b) {
        static_assert(__FFT::FFT_BASE * __FFT::FFT_BASE == BASE);
        int least = (a.size + b.size) << 1, lim = 1 << (std::bit_width(static_cast<uint32_t>(least)) - 1);
        if(lim < least) lim <<= 1;
        __FFT::init(lim);
        using __FFT::arr;
        for(int i = 0; i < a.size; i++) {
            arr[i << 1].real = a.digits[i + 1] % 10000;
            arr[i << 1 | 1].real = a.digits[i + 1] / 10000 % 10000;
        }
        for(int i = 0; i < b.size; i++) {
            arr[i << 1].imag = b.digits[i + 1] % 10000;
            arr[i << 1 | 1].imag = b.digits[i + 1] / 10000 % 10000;
        }
        __FFT::dft(arr, lim);
        for(int i = 0; i < lim; i++) arr[i] *= arr[i];
        __FFT::idft(arr, lim);
        BigInteger res;
        res.resize(a.size + b.size + 1);
        digit_t carry = 0;
        double inv = 0.5 / lim;
        for(int i = 0; i <= a.size + b.size; i++) {
            carry += (digit_t) (arr[i << 1].imag * inv + 0.5);
            carry += (digit_t) (arr[i << 1 | 1].imag * inv + 0.5) * 10000LL;
            res.digits[i + 1] += carry % BASE, carry /= BASE;
        }
        while(res.size > 1 && res.digits[res.size] == 0) res.pop();
        return res;
    }
    BigInteger newton_inv(int n) const {
        if(*this == 0) { std::cerr << "ZeroDivisionError" << '\n'; std::exit(-1); }
        if(std::min(size, n - size) <= NEWTON_DIV_MIN_LEVEL) {
            BigInteger a;
            a.resize(n + 1);
            std::memset(a.digits, 0, sizeof(digit_t) * a.size);
            a.digits[n + 1] = 1;
            return a.divmod(*this, true).first;
        }
        int k = (n - size + 2) >> 1, k2 = k > size ? 0 : size - k;
        BigInteger x = _move_r(k2);
        int n2 = k + x.size;
        BigInteger y = x.newton_inv(n2), a = y + y, b = (*this) * y * y;
        return a._move_l(n - n2 - k2) - b._move_r(2 * (n2 + k2) - n) - 1;
    }
    std::pair<BigInteger, BigInteger> newton_div(const BigInteger &x) const {
        int k = size - x.size + 2, k2 = k > x.size ? 0 : x.size - k;
        BigInteger x2 = x._move_r(k2);
        if(k2 != 0) x2 += 1;
        int n2 = k + x2.size;
        BigInteger u = (*this) * x2.newton_inv(n2);
        BigInteger q = u._move_r(n2 + k2), r = (*this) - q * x;
        while(r >= x) q += 1, r -= x;
        return std::make_pair(q, r);
    }

  public:
    inline void reserve(const int &sz) {
        if(sz < 0) return;
        if(digits != nullptr) delete[] digits;
        capacity = sz, size = 0;
        digits = new digit_t[sz + 1];
        std::memset(digits, 0, sizeof(digit_t) * (sz + 1));
    }

  protected:
    inline void resize(const int &sz) { reserve(sz), size = sz; }

  public:
    BigInteger(): digits(nullptr), flag(true) { *this = 0LL; }
    BigInteger(const BigInteger &x): digits(nullptr) { *this = x; }
    BigInteger(const int64_t &x): digits(nullptr) { *this = x; }
    BigInteger(const std::string &s): digits(nullptr) { *this = s; }
    BigInteger &operator=(const BigInteger &x) {
        if(this == &x) return *this;
        reserve(x.size + 1);
        flag = x.flag, size = x.size;
        std::memcpy(digits, x.digits, sizeof(digit_t) * (x.size + 1));
        return *this;
    }
    BigInteger &operator=(const int64_t &x) {
        flag = (x >= 0), reserve(4);
        if(x == 0) return size = 1, digits[1] = 0, *this;
        if(x == LLONG_MIN) return *this = "-9223372036854775808";
        int64_t n = std::abs(x);
        do { push(n % BASE), n /= BASE; } while(n);
        return *this;
    }
    BigInteger &operator=(const std::string &s) {
        flag = true, reserve(s.size() / WIDTH + 1);
        if(s.empty() || s == "-") return *this = 0;
        int i = 0;
        if(s[0] == '-') flag = false, i++;
        for(int j = s.size() - 1; j >= i; j -= WIDTH) {
            int start = std::max(i, j - WIDTH + 1), len = j - start + 1;
            push(std::stoll(s.substr(start, len)));
        }
        while(size > 1 && digits[size] == 0) pop();
        return *this;
    }
    void clear() {
        if(digits != nullptr) delete[] digits, digits = nullptr;
    }
    ~BigInteger() { clear(); }
    friend std::ostream &operator<<(std::ostream &out, const BigInteger &x) {
        if(!x.flag) out << '-';
        out << (int64_t) x.digits[x.size];
        for(int i = x.size - 1; i >= 1; i--) out << std::setw(WIDTH) << std::setfill('0') << (int64_t) x.digits[i];
        return out;
    }
    friend std::istream &operator>>(std::istream &in, BigInteger &x) {
        std::string s;
        in >> s;
        x = s;
        return in;
    }

    std::string to_string() const {
        std::stringstream ss;
        ss << *this;
        return ss.str();
    }
    int64_t to_long_long() const { return std::stoll(to_string()); }
    std::vector<bool> to_binary() const {
        if(*this == 0) return {0};
        std::vector<bool> res;
        if(flag) {
            for(BigInteger x = *this; x != 0; x = x.div2()) res.emplace_back(x.digits[1] & 1);
            res.emplace_back(0);
            std::reverse(res.begin(), res.end());
            return res;
        } else {
            for(BigInteger x = -*this - 1; x != 0; x = x.div2()) res.emplace_back(!(x.digits[1] & 1));
            res.emplace_back(1);
            std::reverse(res.begin(), res.end());
            return res;
        }
    };
    int _digit_len() const { return size; }
    BigInteger operator-() const {
        if(*this == 0) { return 0; }
        BigInteger res = *this;
        res.flag = !flag;
        return res;
    }
    BigInteger operator~() const { return -(*this) - 1; }
    BigInteger abs() const {
        BigInteger res = *this;
        res.flag = true;
        return res;
    }
    bool operator==(const BigInteger &x) const { return compare(x) == 0; }
    bool operator<(const BigInteger &x) const { return compare(x) < 0; }
    bool operator>(const BigInteger &x) const { return compare(x) > 0; }
    bool operator!=(const BigInteger &x) const { return compare(x) != 0; }
    bool operator<=(const BigInteger &x) const { return compare(x) <= 0; }
    bool operator>=(const BigInteger &x) const { return compare(x) >= 0; }
    BigInteger div2() const {
        BigInteger res = *this;
        for(int i = size; i >= 1; i--) {
            if((res.digits[i] & 1) && (i > 1)) res.digits[i - 1] += BASE;
            res.digits[i] >>= 1;
        }
        while(res.size > 1 && res.digits[res.size] == 0) res.pop();
        return res;
    }
    std::pair<BigInteger, BigInteger> divmod(const BigInteger &x, bool dis_newton = false) const {
        static const int base = BigInteger::BASE;
        BigInteger a = abs(), b = x.abs();
        if(b == 0) { std::cerr << "ZeroDivisionError" << '\n'; std::exit(-1); }
        if(a < b) return std::make_pair(0, flag ? a : -a);
        if(!dis_newton && size > NEWTON_DIV_LIMIT) return newton_div(x);
        int t = base / (x.digits[x.size] + 1);
        a *= t, b *= t;
        int n = a.size, m = b.size;
        BigInteger q = 0, r = 0;
        q.resize(n);
        for(int i = n; i >= 1; i--) {
            r *= base, r += a.digits[i];
            digit_t d1 = m < r.size ? r.digits[m + 1] : 0, d2 = m - 1 < r.size ? r.digits[m] : 0;
            int d = (d1 * base + d2) / b.digits[m];
            r -= b * d;
            while(!r.flag) r += b, d--;
            q.digits[i] = d;
        }
        q.flag = !(flag ^ x.flag), r.flag = flag;
        while(q.size > 1 && q.digits[q.size] == 0) q.pop();
        return std::make_pair(q, r / t);
    }
    inline BigInteger _move_r(int d) const {
        if(*this == 0 || d >= size) return 0;
        if(d == 0) return *this;
        BigInteger res;
        res.reserve(size - d + 1);
        for(int i = d + 1; i <= size; i++) res.push(digits[i]);
        return res;
    }
    inline BigInteger _move_l(int d) const {
        if(*this == 0) return 0;
        if(d == 0) return *this;
        BigInteger res;
        res.reserve(size + d + 1);
        for(int i = 1; i <= d; i++) res.push(0);
        for(int i = 1; i <= size; i++) res.push(digits[i]);
        return res;
    }
    BigInteger operator+(const BigInteger &x) const {
        if(!x.flag) return *this - x.abs();
        if(!flag) return x - abs();
        BigInteger res;
        res.flag = !(flag ^ x.flag);
        int n = std::max(size, x.size) + 1;
        res.reserve(n);
        digit_t carry = 0;
        for(int i = 1; i <= n; i++) {
            digit_t d1 = i <= size ? digits[i] : 0, d2 = i <= x.size ? x.digits[i] : 0;
            res.push(d1 + d2 + carry);
            carry = res.digits[i] / BASE;
            res.digits[i] %= BASE;
        }
        while(res.size > 1 && res.digits[res.size] == 0) res.pop();
        return res;
    }
    BigInteger operator-(const BigInteger &x) const {
        if(!x.flag) return *this + x.abs();
        if(!flag) return -(abs() + x);
        BigInteger res;
        if(*this < x) res.flag = false;
        digit_t carry = 0;
        int n = std::max(size, x.size);
        res.reserve(n);
        for(int i = 1; i <= n; i++) {
            digit_t d1 = i <= size ? digits[i] : 0, d2 = i <= x.size ? x.digits[i] : 0;
            if(res.flag) res.push(d1 - d2 - carry);
            else res.push(d2 - d1 - carry);
            if(res.digits[i] < 0) res.digits[i] += BASE, carry = 1;
            else carry = 0;
        }
        while(res.size > 1 && res.digits[res.size] == 0) res.pop();
        return res;
    }
    BigInteger operator*(const BigInteger &x) const {
        BigInteger zero = 0;
        if(*this == zero || x == zero) return zero;
        int n = size, m = x.size;
        int64_t lim = 1LL * n * m;

        if(lim >= FFT_LIMIT) {
            BigInteger res = fft_mul(*this, x);
            res.flag = !(flag ^ x.flag);
            return res;
        }

        BigInteger res;
        res.flag = !(flag ^ x.flag);
        res.resize(n + m + 2);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                res.digits[i + j - 1] += digits[i] * x.digits[j];
                res.digits[i + j] += res.digits[i + j - 1] / BASE;
                res.digits[i + j - 1] %= BASE;
            }
        }
        for(int i = 1; i <= n + m + 1; i++) {
            res.digits[i + 1] += res.digits[i] / BASE;
            res.digits[i] %= BASE;
        }
        while(res.size > 1 && res.digits[res.size] == 0) res.pop();
        return res;
    }
    BigInteger &operator*=(int x) {
        if(x == 0 || *this == 0) return *this = 0;
        if(x < 0) flag = !flag, x = -x;
        digit_t carry = 0;
        for(int i = 1; i <= size || carry; i++) {
            if(i > size) push(0);
            digit_t cur = digits[i] * x + carry;
            carry = cur / BigInteger::BASE;
            digits[i] = cur % BigInteger::BASE;
        }
        while(size > 1 && digits[size] == 0) pop();
        return *this;
    }
    BigInteger operator*(const int &x) const {
        BigInteger t = *this;
        return t *= x;
    }
    BigInteger operator/(const int64_t &x) const {
        if(x == 0) { std::cerr << "ZeroDivisionError" << '\n'; std::exit(-1); }
        if(*this == 0) return 0;
        if(x == 2) return div2();
        if(x == -2) {
            BigInteger res = div2();
            res.flag = !res.flag;
            return res;
        }

        BigInteger res;
        res.flag = !(flag ^ (x >= 0));

        digit_t cur = 0, div = std::abs(x);
        res.resize(size);

        for(int i = size; i >= 1; i--) {
            cur = cur * BASE + digits[i];
            res.digits[i] = res.flag ? (cur / div) : (-cur / -div);
            cur %= div;
        }
        while(res.size > 1 && res.digits[res.size] == 0) res.pop();
        return res;
    }
    BigInteger operator/(const BigInteger &x) const { return divmod(x).first; }
    BigInteger operator%(const int64_t &x) const {
        if(x == 2 || x == 4 || x == 5) { return digits[1] % x; }
        return *this - (*this / x * x);
    }
    BigInteger operator%(const BigInteger &x) const { return divmod(x).second; }
    BigInteger &operator+=(const BigInteger &x) { return *this = *this + x; }
    BigInteger &operator-=(const BigInteger &x) { return *this = *this - x; }
    BigInteger &operator*=(const BigInteger &x) { return *this = *this * x; }
    BigInteger &operator/=(const int64_t &x) { return *this = *this / x; }
    BigInteger &operator/=(const BigInteger &x) { return *this = *this / x; }
    BigInteger &operator%=(const int64_t &x) { return *this = *this % x; }
    BigInteger &operator%=(const BigInteger &x) { return *this = *this % x; }
    BigInteger &operator++() { return *this += 1; }
    BigInteger operator++(int) {
        BigInteger t = *this;
        return *this += 1, t;
    }
    BigInteger &operator--() { return *this -= 1; }
    BigInteger operator--(int) {
        BigInteger t = *this;
        return *this -= 1, t;
    }
};