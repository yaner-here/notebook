# 线性DP

> [洛谷P15360](https://www.luogu.com.cn/problem/P15360)：给定平面上的`n<=5e3`个横坐标递增的点`int x[1->n], y[1->n]`，依次做线性插值得到函数$f(x)$。现在删除其中除了首尾以外的`m`个点，剩余的点做线性插值得到函数$f'(x)$。若$|f(x)-f'(x)|\le d$恒成立，求`m`的最大值。

令`dp[i]`表示给定前`i`个点，且选中第`i`个点时，能删除的点的数量最大值。考虑在删除了若干个点的$f'(x)$中，第`i`个点的前面是点`j`，则在`x,y[j+1 -> i-1]`这`i-j-1`个点中，每个点都会对斜率造成一定的区间要求。最终要求第`i`点与第`j`的点形成的斜线斜率`k`需要属于这个斜率区间`[k_min, k_max]`内，**这等价于两个要求**：`k_min <= k_max`、`k_min <= k && k <= k_max`。本题对精度要求较高，要么用`long double`，要么用`Frac`分数板子。

```c++
const int N_MAX = 5e3, X_MAX = 1e9, Y_MAX = 1e9, D_MAX = 1e9;
int q, n, d, x[1 + N_MAX], y[1 + N_MAX], dp[1 + N_MAX];
Frac<int64_t> k, k_max, k_min;
int main() {
    std::cin >> q;
    while(q--) {
        std::cin >> n >> d;
        for(int i = 1; i <= n; ++i) { std::cin >> x[i]; }
        for(int i = 1; i <= n; ++i) { std::cin >> y[i]; }

        std::fill(dp, dp + 1 + n, 0); dp[1] = dp[2] = 0;
        for(int i = 3, j; i <= n; ++i) {
            k_min = {-Y_MAX - D_MAX, 1}; k_max = {Y_MAX + D_MAX, 1};
            for(j = i - 1; j >= 1; --j) {
                k = Frac<int64_t>{y[i] - y[j], x[i] - x[j]}; k.simplify();
                k_max = std::min(k_max, Frac<int64_t>{y[i] - y[j] + d, x[i] - x[j]}); k_max = k_max.simplify();
                k_min = std::max(k_min, Frac<int64_t>{y[i] - y[j] - d, x[i] - x[j]}); k_min = k_min.simplify();
                if(k_max < k_min) { break; }
                if(k_min <= k && k <= k_max) { dp[i] = std::max(dp[i], dp[j] + i - j - 1); }
            }
        }
        std::cout << dp[n] << '\n';
    }
}
```

# 并查集

> [洛谷P2189](https://www.luogu.com.cn/problem/P2189)：给定包含`n<=1e5`个顶点与`m<=2e5`条无向边构成的图。执行`q`次查询，每次查询给编号为`src[1->k]`的节点安装一次性报警器，初始时从`src[1]`出发，依次经过`src[1->k]`的各个点， 只有首次到达含有一次性报警器的节点时才会报警，请判断是否存在一条路径，使得报警顺序恰好为`src[1->k]`。

首先我们注意到，如果两个节点之间存在不触发报警器的路径，则显然它们可以称为一个“联通块”。因此，我们将所有符合该条件的节点视为一个整体，可以用并查集来维护。也就是说，如果两个节点不再同一个“联通块”中，则它们之间必定存在一个含有报警器的节点，分开了这两个“联通块”。特殊地，每个报警器节点自成一个“联通块”。

由于报警器是一次性的，因此每到达一个报警器节点，我们还需要将它与周围相连的联通块进行合并。于是问题等价地转化为：判断`dsu_find(src[i-1]) == dsu_find(src[i])`是否成立，如果不成立，则说明`src[i-1] -> src[i]`必定会经过另外一个报警器节点，不满足题意。

```c++
const int N_MAX = 1e5, M_MAX = 2e5, K_MAX = N_MAX, Q_MAX = 5;
int n, m, k, q, u_tmp, v_tmp, src[1 + N_MAX]; bool ans;

int edge_first[1 + N_MAX], edge_next[1 + 2 * M_MAX], edge_to[1 + 2 * M_MAX], edge_count; bool vertex_vis[1 + N_MAX], vertex_src[1 + N_MAX];
inline void edge_add(const int &u, const int &v) {
    edge_to[++edge_count] = v;
    edge_next[edge_count] = edge_first[u];
    edge_first[u] = edge_count;
}

int dsu_father[1 + N_MAX];
inline void dsu_init(int n) { std::iota(dsu_father, dsu_father + 1 + n, 0); }
inline int dsu_find(int x) { return dsu_father[x] == x ? x : dsu_father[x] = dsu_find(dsu_father[x]); }
inline void dsu_unite(int child, int root) { child = dsu_find(child); root = dsu_find(root); if(child != root) { dsu_father[child] = root; } }

int main() {
    std::cin >> n >> m >> k >> q;
    for(int i = 1; i <= m; ++i) { std::cin >> u_tmp >> v_tmp; edge_add(u_tmp, v_tmp); edge_add(v_tmp, u_tmp); }

    while(q--) {
        std::fill(vertex_src + 1, vertex_src + 1 + n, false);
        std::fill(vertex_vis + 1, vertex_vis + 1 + n, false);
        for(int i = 1; i <= k; ++i) { std::cin >> src[i]; vertex_src[src[i]] = true; }
        
        dsu_init(n);
        for(int i = 1; i <= n; ++i) {
            if(vertex_vis[i] == true) { continue; }
            std::queue<int> queue; queue.push(i);
            while(!queue.empty()) {
                int u = queue.front(); queue.pop();
                if(vertex_src[u] == true) { continue; }
                if(vertex_vis[u] == true) { continue; } vertex_vis[u] = true;
                dsu_unite(u, i);
                for(int j = edge_first[u]; j != 0; j = edge_next[j]) {
                    int &v = edge_to[j];
                    if(vertex_src[v] == false && vertex_vis[v] == false) { queue.push(v); }
                }
            }
        }

        ans = true;
        for(int i = 1; i <= k; ++i) {
            int &u = src[i]; vertex_src[u] = false;
            for(int j = edge_first[u]; j != 0; j = edge_next[j]) {
                int &v = edge_to[j];
                if(vertex_src[v] == false) { dsu_unite(u, v); }
            }
            if(i >= 2 && dsu_find(src[i - 1]) != dsu_find(src[i])) {
                ans = false;
                break;
            }
        }
        std::cout << (ans ? "Yes" : "No") << '\n';
    }
}
```

# 数论 - 合数逆元

> [洛谷P2174](https://www.luogu.com.cn/problem/P2174)：请实现一个初始值已给定的可重集，支持`q<=1e6`次操作：（1）删除一个`x_tmp`，保证`x_tmp`一定存在；（2）查询最大值；（3）查询最小值；（4）查询$最大值^{最小值}$，模`317847191`输出；（5）查询所有元素的成绩，模`317847191`输出。请注意：`317847191 = 71 × 113 × 173 × 229`。

不妨记$p = \displaystyle\prod p_i^{k_i}$。本题的难点在于模数`p`不是质数，因此不能保证其逆元一定存在。对于这种情况，我们的通用思路是：任意一个值都可以拆分为纯$p_j$部分、与不含任何$p_j$的部分，即$x_i=\left(\displaystyle\frac{x_i}{p_{j}^{m_{ij}}}\right)\times p_{j}^{m_{ij}}$。于是对于操作（5）而言，令答案为$x$，则$x = \displaystyle\prod_{i=1}^{n} x_i = \prod_{i=1}^{n}{\left(\displaystyle\frac{x_i}{p_{j}^{m_{ij}}}\times p_{j}^{m_{ij}}\right)} = \prod_{i=1}^{n}{\left(\displaystyle\frac{x_i}{p_{j}^{m_{ij}}}\right) } \times p_{j}^{\sum_{i=1}^{n}m_{ij}} = \textcolor{red}{\mathrm{x\_prod\_div\_p}[j]} \times p_{j}^{\textcolor{green}{\mathrm{p\_cnt}[j]}}$，两侧同时对$p_j^{k_j}$取模可以得到一个同余方程。我们对每个$p_j$都依次类推，可以得到一个同余方程组，直接使用中国剩余定理即可解得$x$的值。

```c++
int64_t gcd(int64_t a, int64_t b) { return b == 0 ? a : gcd(b, a % b); }
std::tuple<int64_t, int64_t, int64_t> exgcd(const int64_t &a, const int64_t &b) { /* ax + by = gcd(a, b); return {gcd, x, y}; */ if (b == 0) { return {a, 1, 0}; } auto [gcd, x, y] = exgcd(b, a % b); return {gcd, y, x - a / b * y}; }

template<typename T> inline T fast_pow(T a, int64_t b) { T ans = 1; for(; b > 0; a = a * a, b /= 2) { if(b % 2) { ans = ans * a; } } return ans; }
template<typename T> inline T fast_pow(T a, int64_t b, const int64_t &p) { T ans = 1; for(a = a % p; b > 0; a = (a * a) % p, b /= 2) { if(b % 2) { ans = (ans * a) % p; } } return ans; }

constexpr inline int64_t mod(const int64_t &x, const int64_t &p) { return (x % p + p) % p; }
inline int64_t mul_mod(const int64_t &x, const int64_t &y, const int64_t &p) { return (mod(x, p) * mod(y, p)) % p; }
inline int64_t mul_mod(const std::initializer_list<int64_t> &x, const int64_t &p) { return std::accumulate(x.begin(), x.end(), 1ll, [&p](int64_t acc, int64_t v) { return mul_mod(acc, v, p); }); }
inline int64_t safe_mul_mod(int64_t x, int64_t y, const int64_t &p) { int64_t ans = 0; for(ans = 0; y > 0; x = (x * 2) % p, y /= 2) { if(y & 1) { ans = (ans + x) % p; } } return ans; }
inline int64_t safe_mul_mod(const std::initializer_list<int64_t> &x, const int64_t &p) { return std::accumulate(x.begin(), x.end(), 1ll, [&p](int64_t acc, int64_t v) { return safe_mul_mod(acc, v, p); }); }

inline int64_t inv_mod(const int64_t a, const int64_t p) { return fast_pow(a, p - 2, p); }
inline int64_t inv_exgcd_mod(const int64_t a, const int64_t &p) { auto [gcd_a_p, x, y] = exgcd(a, p); assert(gcd_a_p == 1); return mod(x, p / gcd_a_p); }

const int N_MAX = 1e6, Q_MAX = 1e6, P_LEN_MAX = 4;
int64_t p = 317847191, p_len = 4, p_base[1 + P_LEN_MAX] = {0, 71, 113, 173, 229}, p_power[1 + P_LEN_MAX] = {0, 1, 1, 1, 1};
int n, q; std::multiset<int64_t> s; char op_tmp; int64_t x_tmp;
int64_t p_cnt[1 + P_LEN_MAX], x_prod_div_p[1 + P_LEN_MAX] = {0, 1, 1, 1, 1};
int main(){
    std::ios::sync_with_stdio(false); std::cin.tie(nullptr);
    std::cin >> n >> q;
    for(int i = 1; i <= n; ++i) { std::cin >> x_tmp; s.insert(x_tmp); }
    
    for(auto x_tmp : s) {
        for(int j = 1; j <= p_len; ++j) {
            int64_t x = x_tmp;
            while(x % p_base[j] == 0) { ++p_cnt[j]; x /= p_base[j]; }
            x_prod_div_p[j] = mul_mod(x_prod_div_p[j], x, p_base[j]);
        }
    }

    while(q--) {
        std::cin >> op_tmp;
        if(op_tmp == 'D') {
            std::cin >> x_tmp;
            for(int i = 1; i <= p_len; ++i) {
                int64_t x = x_tmp;
                while(x % p_base[i] == 0) { --p_cnt[i]; x /= p_base[i]; }
                x_prod_div_p[i] = mul_mod(x_prod_div_p[i], inv_exgcd_mod(x, p_base[i]), p_base[i]);
            }
            s.erase(s.find(x_tmp));
        } else if(op_tmp == 'B') {
            std::cout << *s.rbegin() << '\n';
        } else if(op_tmp == 'S') {
            std::cout << *s.begin() << '\n';
        } else if(op_tmp == 'M') {
            std::cout << fast_pow(*s.rbegin(), *s.begin(), p) << '\n';
        } else if(op_tmp == 'T') {
            int64_t ans = 0;
            for(int i = 1; i <= p_len; ++i) {
                int64_t a = mul_mod(x_prod_div_p[i], fast_pow(p_base[i], p_cnt[i], p_base[i]), p_base[i]);
                int64_t m = p / p_base[i];
                int64_t m_inv = inv_exgcd_mod(m, p_base[i]);
                ans += mul_mod({a, m, m_inv}, p); ans = mod(ans, p);
            }
            std::cout << ans << '\n';
        }
    }
}
```

# 组合数学 - 卡特兰数

> [洛谷P1641](https://www.luogu.com.cn/problem/P1641)：给定`n`个字符`1`与`m`个字符`0`构成的字符串，如果其任意长度的前缀均满足`1`的数量大于等于`0`的数量，则称该字符串合法。求合法的字符串总数量，答案模`20100403`输出。

卡特兰数板子题。

```c++
const int N_MAX = 1e6, M_MAX = 1e6; const int64_t MOD = 20100403;
int n, m;

int64_t fact[1 + N_MAX + M_MAX], fact_inv[1 + N_MAX + M_MAX];
inline int64_t C(const int64_t n, const int64_t m, const int64_t &p) {
    if(m < 0) { return 0; }
    // if(m >= 0 && n >= m) { return mul_mod({fact[n], fact_inv[m], fact_inv[n - m]}, p); }
    if(m >= 0 && n >= m) { return fact[n] * fact_inv[m] % p * fact_inv[n - m] % p; }
    if(m >= 0 && 0 <= n && n < m) { return 0; }
    if(m >= 0 && n < 0) { return (m % 2 == 0 ? 1 : -1) * C(m - n - 1, m, p); }
    assert(false && "impossible");
    return -1;
}

int main() {
    fact[0] = 1; for(int i = 1; i <= N_MAX + M_MAX; ++i) { fact[i] = fact[i - 1] * i % MOD; }
    fact_inv[N_MAX + M_MAX] = inv_mod(fact[N_MAX + M_MAX], MOD); for(int i = N_MAX + M_MAX - 1; i >= 0; --i) { fact_inv[i] = (fact_inv[i + 1] * (i + 1)) % MOD; }

    std::cin >> n >> m;
    std::cout << mod(C(n + m, m, MOD) - C(n + m, m - 1, MOD), MOD);
}
```

> [洛谷P5014](https://www.luogu.com.cn/problem/P5014)：给定一个杨辉三角图形，从左向右、从上到下地给每个节点从`1`开始编号。每个节点在每一步都可以到达左下方或右下方的节点，求从节点`1`出发到节点`u[1->q]<=5e11+5e5`的方案数有多少，答案模`998244353`输出。

不妨将杨辉三角图形做同胚变换：

```
1
| \
2 - 3
| \ | \
4 - 5 - 6
| \ | \ | \
7 - 8 - 9 - 10
......
```

令向下为`x`轴正方向，向右为`y`轴正方向，于是问题转化为：从`(1, 1)`到`(n, m)`的方案数有多少。显然`u -> (n<=1e6, m)`是一一对应的关系，使用二分可以方便地求出`n`的值，再经过一次减法得到`m`的值。由于本题是从`(1, 1)`开始出发，因此为了方便起见，我们将问题改写为从`(0, 0)`到`(n-1, m-1)`的方案数有多少。**接下来的讨论均默认已执行`n -= 1; m -= 1;`**。

如果没有斜边的存在，则本题显然为卡特兰数模板题——一定会向下`n`次、向右`m`次，且`n>=m`，总共操作`n+m`次。现在引入了斜边，等价于同时向下与向右，因此**不妨令走了`i`次斜边**，则一定会向下`n-i`次、向右`m-i`次，**总共操作`n+m-2i + i == n-m-i`次**。我们分两方面考虑：

1. `i`次斜边可以安排在`n+m-i`的任何`i`个位置处，因此斜边的执行位置会产生$C_{n+m-i}^{i}$中情况。
2. 向下`n-i`次、向右`m-i`、且`n-1<=m-1`，因此仍然是卡特兰数模板题，直接套结论：$C_{n+m-2i}^{m-i} - C_{n+m-2i}^{m-i-1}$。

注意到`i`的取值范围为`[0, min(n, m)] = [0, m]`，因此我们可得最终答案：

$$
\displaystyle\sum_{i=0}^{m} C_{n+m-i}^{i} \times \left( C_{n+m-2i}^{m-i} - C_{n+m-2i}^{m-i-1} \right)
$$

```c++
const int Q_MAX = 100; const int64_t U_MAX = 5e11 + 5e5, N_MAX = 1e6, M_MAX = 1e6; const int64_t MOD = 998244353;
int q; int64_t u[1 + Q_MAX], n, m, n_left, n_right, n_mid, ans;
int64_t fact[1 + N_MAX + M_MAX], fact_inv[1 + N_MAX + M_MAX];

inline int64_t C(const int64_t n, const int64_t m, const int64_t &p) {
    if(m < 0) { return 0; }
    // if(m >= 0 && n >= m) { return mul_mod({fact[n], fact_inv[m], fact_inv[n - m]}, p); }
    if(m >= 0 && n >= m) { return fact[n] * fact_inv[m] % p * fact_inv[n - m] % p; }
    if(m >= 0 && 0 <= n && n < m) { return 0; }
    if(m >= 0 && n < 0) { return (m % 2 == 0 ? 1 : -1) * C(m - n - 1, m, p); }
    assert(false && "impossible"); return -1;
}

int main() {
    fact[0] = 1; for(int i = 1; i <= N_MAX + M_MAX; ++i) { fact[i] = fact[i - 1] * i % MOD; }
    fact_inv[N_MAX + M_MAX] = inv_mod(fact[N_MAX + M_MAX], MOD); for(int i = N_MAX + M_MAX - 1; i >= 0; --i) { fact_inv[i] = (fact_inv[i + 1] * (i + 1)) % MOD; }
    
    std::cin >> q; 
    for(int i = 1; i <= q; ++i) { std::cin >> u[i]; }
    
    for(int i = 1; i <= q; ++i) {
        n_left = 1; n_right = N_MAX;
        while(n_left <= n_right) {
            n_mid = (n_left + n_right) / 2;
            if(n_mid * (n_mid - 1) / 2 + 1 <= u[i]) {
                n_left = n_mid + 1;
            } else {
                n_right = n_mid - 1;
            }
        }
        n = n_right; m = u[i] - n * (n - 1) / 2; ans = 0; --n; --m;
        for(int j = 0; j <= m; ++j) {
            ans += C(n + m - j, j, MOD) * mod(C(n + m - 2 * j, m - j, MOD) - C(n + m - 2 * j, m - j - 1, MOD), MOD);
            ans %= MOD;
        }
        std::cout << ans << '\n';
    }
}
```