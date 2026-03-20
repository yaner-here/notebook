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
