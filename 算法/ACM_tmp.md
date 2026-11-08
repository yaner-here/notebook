，给定无向边权图$\mathcal{G}=\{\mathcal{V},\mathcal{E}\}$，如果存在边的子集$\mathcal{M}$满足$\forall (u_1, v_1),(u_2, v_2)\in\mathcal{M}, u_1\neq v_1\neq u_2 \neq v_2$两两互不相等，则称$\mathcal{M}$为图$\mathcal{G}$的一个**匹配**。显然一个图存在多个匹配。

- 匹配边/非匹配边：$\mathcal{M}$/$\mathcal{E}-\mathcal{M}$中的元素(边)。
- 匹配点/非匹配点：$\{v\mid \exists u, (u, v)\in\mathcal{M}\}$ / $\{v\mid \not\exists u, (u, v)\in\mathcal{M}\}$中的元素(顶点)。
- 交错路：由匹配边和非匹配边交错构成的路径。
- 增广路：从非匹配点出发，到非匹配点终止的路径。
- 匹配的大小：$\mathcal{M}$中元素的数量，记为$\#(\mathcal{M})$。
- 最大匹配/最大权匹配：$\underset{\mathcal{M}}{\mathrm{argmax}}\#(\mathcal{M})$ / $\underset{\mathcal{M}}{\mathrm{argmax}}\displaystyle\sum_{\forall e\in\mathcal{M}}w_e$。
- **重要结论**：$N = 二部图最大匹配 + 二部图最大独立集$。

#### 二分图最大匹配

**二分图最大匹配本质上研究的是“匹配关系”（边）的最大数量，要求选出的边不能有重复的顶点。**

> [洛谷P3386](https://www.luogu.com.cn/problem/P3386)：二分图最大匹配模板题。给定一个二分图，左半部分与右半部分分别有`n_1<=5e2`和`n_2<=5e2`个点，一共有`m<=5e4`条无向边。求最大匹配的大小。

使用匈牙利算法：遍历左半部分的每个点`u`进行一次DFS，在DFS之前清空`vis[]`数组，然后遍历所有与其相邻的右半部分的点`v`，如果`v`尚未被左半部分的点匹配（即`match[v] == 0`），则直接贪心地让`(u, v)`匹配；如果`v`已经被左半部分的点`u' = mathc[v]`匹配了（即`match[v] != 0`），则`u`尝试抢占`v`，并对原先匹配的`u'`做一次`dfs(u')`，让`u'`尝试去抢占右侧部分的其它点。依次类推，若最后一次DFS报告可以抢占，则全部DFS都可以抢占，从而使得匹配的大小加`1`。于是DFS成功的充要条件为找到了一条增广路，成功的次数即为产生的匹配大小，遍历左半部分的每个点`u`就能得到最大匹配的大小。

虽然是无向图，但是在该DFS算法中，从左到右才需要遍历边，从右到左只需要通过`match[v]`即可。因此我们只需要保留从左到右的一次有向边即可。

该算法需遍历左侧部分的$O(n_1)$个点，每个点最坏情况下会遍历全部的$O(m)$条边。于是该算法最坏情况下的时间复杂度为$O(n_1m)$。然而在现实情况中，随机数据很难卡到最坏情况。为避免这种情况，实战中一般会随机打乱点遍历的顺序。

```c++
const int N_MAX = 1000, M_MAX = 5e4;
int n_1, n_2, m, u_tmp, v_tmp, ans; std::vector<int> g[1 + N_MAX];
int match[1 + N_MAX]; bool vis[1 + N_MAX];

bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v]) == true) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n_1 >> n_2 >> m;
    for(int i = 1; i <= m; ++i) { std::cin >> u_tmp >> v_tmp; g[u_tmp].push_back(v_tmp); }

    for(int u = 1; u <= n_1; ++u) {
        std::fill(vis + 1, vis + 1 + n_1 + n_2, false);
        ans += dfs(u);
    }
    std::cout << ans;
}
```

该算法有几个常用的时间常数优化，实战证明以下的优化效果局限性很大：

- 由于时间复杂度是$O(n_1m)$，因此通常选择左右子图中节点数量较少的那一部分进行遍历，因此时间复杂度可以降低到$O(\min(n_1, n_2)\cdot m)$。
- 注意到一旦一次`dfs(u)`返回了`false`，则意味着与其所有直接相邻的`v`都无法再形成增广路了。因此对于`dfs(u')`而言，可以直接排除这些`v`。这给了我们一个启示：如果`dfs(u)`未发现增广路，则其产生的`vis[]`依然可以被后续的`dfs(u')`重复利用，从而减少清空`vis[]`的频次，直到发现增广路才需要清空。于是我们清空`vis[]`的次数等于发现增广路的次数，即时间复杂度降低到了$O((\#(\mathcal{M})+1)\cdot m)\approx O(\#(\mathcal{M})\cdot m)$。
- 注意到一次`dfs(u)`如果返回`true`，通常会有两种情况：找到了未匹配的点`v`，或者能抢占已匹配的点`v`。显然前者速度更快，因此语气对着一个已匹配的点做抢占，不如优先选择未匹配的点`v`。
- 由于我们在DFS中只通过左子图的点来遍历右子图的点，只通过`match[]`数组来从右子图的点查找左子图匹配的点，因此不需要为邻接表`std::vector<int> g[*]`开辟$O(n_1+n_2)$的空间，只需要开辟$O(n_1)$即可。同理，只需要为`match[*]`开辟$O(n_2)$的空间。更进一步地，**甚至左右子图的编号都可以重复，例如左子图的点编号为`1->n_1`，右子图编号为`1->n_2`**。因此我们可以不再使用预先分配好的`vis[]`、`match[]`、`g[]`数组，而是直接使用`std::map<>`（`std::unordered_map`会更快）来进行任意点序号的映射，避免考虑数组预分配长度问题。**但是这会极大的影响算法的时间常数**。

```c++
const int N_MAX = 1000, M_MAX = 2.5e5;
int n_1, n_2, m, u_tmp, v_tmp, ans; 
// std::vector<int> g[1 + N_MAX]; int match[1 + N_MAX]; bool vis[1 + N_MAX];
std::map<int, std::vector<int>> g; std::map<int, int> match; std::map<int, bool> vis;

bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; }
        if(match[v] == 0) { vis[v] = true; match[v] = u; return true; }
    }
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(dfs(match[v]) == true) { match[v] = u; return true; }
    }
    return false;
}

int main() {
    std::cin >> n_1 >> n_2 >> m;
    if(n_1 < n_2) {
        for(int i = 1; i <= m; ++i) { std::cin >> u_tmp >> v_tmp; g[u_tmp].push_back(v_tmp); }
    } else {
        std::swap(n_1, n_2);
        for(int i = 1; i <= m; ++i) { std::cin >> u_tmp >> v_tmp; g[v_tmp].push_back(u_tmp); }
    }

    bool flag = false; 
    for(int u = 1; u <= n_1; ++u) {
        if(flag == true) { 
	        // std::fill(vis + 1, vis + 1 + n_1 + n_2, false); 
	        vis.clear();
	    }
        ans += (flag = dfs(u));
    }
    std::cout << ans;
}
```

> [洛谷P1129](https://www.luogu.com.cn/problem/P1129)：给定`q<=20`次查询。每次查询一个数组`bool a[1->n<=200][1->n<=200]`，现允许任意次交换任意两行或任意两列，是否能使得主对角线上的元素`i:1->n, a[i][i]`均为`true`？如果能，则输出`Yes`，反之输出`No`。

注意到原题的要求等价于**数组`a[*][*]`内存在`n`个`true`元素，它们之间两两不共行、两两不共列**，等价于**每一行有且仅有一个被选中的`true`元素，每一列有且仅有一个被选中的`true`元素**，等价于**每一行能且仅能匹配到一列，每一列能且仅能匹配到一行**。因此我们可以将`n`个行视为左子图的点集，`n`个列视为右子图的点集，`a[i][j] == true`表示行`i`与列`j`之间存在一条无向边，于是问题转化为**二分图的最大匹配大小是否大于等于`n`**，在本题中这个值显然不可能大于`n`，因此也可以记为**二分图的最大匹配大小是否等于`n`**。

```c++
const int Q_MAX = 20, N_MAX = 200;
int q, n, ans; bool a_tmp; std::vector<int> g[1 + N_MAX]; bool vis[1 + N_MAX]; int match[1 + N_MAX];

bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v]) == true) {
            match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> q;
    while(q--) {
        std::cin >> n; 
        for(int i = 1; i <= n; ++i) { g[i].clear(); }
        for(int i = 1; i <= n; ++i) {for(int j = 1; j <= n; ++j) {std::cin >> a_tmp; if(a_tmp == true) { g[i].push_back(j); }}}
        
        ans = 0; std::fill(match + 1, match + 1 + n, 0);
        for(int u = 1; u <= n; ++u) { std::fill(vis + 1, vis + 1 + n, false); ans += dfs(u); }
        std::cout << (ans >= n ? "Yes" : "No") << '\n';
    }
}
```

> [洛谷P4905](https://www.luogu.com.cn/problem/P4905)：给定棋盘`bool map[1->n<=100][1->n<=100]`，其中恰好有`k<=100`个格子的`map[i][j] == true`，表示该处禁止摆放木块。现有无限个尺寸为`2×1`的木块，木块之间不得重叠，请问棋盘上最多能摆放多少木块？

不妨按国际棋盘风格对格子进行交替染色，即$\begin{cases}(i+j)\% 2 = 1 \Leftrightarrow (i, j)为黑色\\(i+j)\%2 = 0 \Leftrightarrow (i, j)为白色 \end{cases}$，显然每个木块必定占用一个黑块和一个白块。于是棋盘上摆放一个木块，等价于一个相邻的黑块与白块进行了匹配。于是可以认为`n_1`个黑块与`n_2`个白块分别构成了两个子图，若第`i`个黑块与第`j`个白块相邻，且两者均可用，则存在一条无向边`(i, j)`，问题转化为求解二部图最大匹配的大小。

这里我们以`(i * n + j)`为`(i, j)`编号，下标从`0`开始。

```c++
const int N_MAX = 100, K_MAX = 100, DIR[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int n, k, u_tmp, v_tmp, ans; std::set<std::pair<int, int>> set;
std::vector<int> g[N_MAX * N_MAX]; int match[N_MAX * N_MAX]; bool vis[N_MAX * N_MAX];

bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v]) == true) {
            match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n >> k;
    for(int i = 1; i <= k; ++i) { std::cin >> u_tmp >> v_tmp; --u_tmp; --v_tmp; set.emplace(u_tmp, v_tmp); }

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            if((i + j) % 2 == 0 || set.count({i, j}) >= 1) { continue; }
            for(int p = 0; p < 4; ++p) {
                int i_new = i + DIR[p][0], j_new = j + DIR[p][1];
                if(i_new < 0 || i_new >= n || j_new < 0 || j_new >= n || set.count({i_new, j_new}) >= 1) { continue; }
                g[i * n + j].push_back(i_new * n + j_new);
            }
        }
    }

    for(int i = 0; i < n; ++i) { for(int j = 0; j < n; ++j) {
        if((i + j) % 2 == 0) { continue; }
        std::fill(vis, vis + (n * n), false);
        ans += dfs(i * n + j);
    }}
    std::cout << ans;
}
```

> [洛谷P2071](https://www.luogu.com.cn/problem/P2071)：现有`n<=2e3`排坐位与`2n`个人，每排座位有`2`个座位。每一个人都有自己偏好的`2`个座位排号`a[1->2n][2]`。求最多能满足多少人的偏好。

本题的问题在于，一个座位排节点可以与两个人节点相连，不符合原教旨主义的、一对一的“匹配”概念。于是我们可以为一排座位创建两个座位节点。也就是说，一个人`u`偏好于两排座位`v1, v2`，则可以创建双倍数量的无向边：`u -> v1_1, u -> v1_2, u -> v2_1, u -> v2_2`。

```c++
const int N_MAX = 2000;
int n, u_tmp, v_tmp, ans;
std::map<int, std::vector<int>> g; std::map<int, int> match; std::map<int, bool> vis;

bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v])) {
            match[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n;
    for(int i = 1; i <= n * 2; ++i) { 
        std::cin >> u_tmp >> v_tmp;
        g[i].push_back(u_tmp * 2); g[i].push_back(u_tmp * 2 - 1); 
        g[i].push_back(v_tmp * 2); g[i].push_back(v_tmp * 2 - 1); 
    }

    for(int u = 1; u <= n * 2; ++u) {
        vis.clear();
        ans += dfs(u);
    }
    std::cout << ans;
}
```

> [洛谷P2055](https://www.luogu.com.cn/problem/P2055)：给定`q<=20`次查询。每次查询给定`n<=50`个学生，`g_has_bed[i:1->n]`表示是否拥有自己的床位，`g_need_bed[i:1->n]`表示是否需要床位，`g_relation[i:1->n][j:1->n]`表示学生`i`是否可以住到学生`j`的床位（本题中为对阵矩阵，不保证对角线的值）。请判断是否存在一种匹配方式，让所有需要床位的学生都能住宿。

显然把学生和床位拆成两个子图。学生`i`能住到学生`j`床位的充要条件是：学生`i`需要床位(`g_need_bed[i]==1`)、学生`j`拥有床位(`g_has_bed[j]==1`)、学生`i`与学生`j`之间互相认识`g_relation[i][j] == 1 || i == j`。

```c++
const int Q_MAX = 20, N_MAX = 50;
int q, n, m, flag_tmp, ans;

int g_has_bed[1 + N_MAX], g_need_bed[1 + N_MAX];
std::vector<int> g[1 + N_MAX]; int g_match[1 + N_MAX]; bool g_vis[1 + N_MAX];
bool dfs(int u) {
    for(int v : g[u]) {
        if(g_vis[v] == true) { continue; } g_vis[v] = true;
        if(g_match[v] == 0 || dfs(g_match[v]) == true) {
            g_match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> q; while(q--) {
        std::cin >> n; ans = 0; std::fill(g_match + 1, g_match + 1 + n, false); for(int i = 1; i <= n; ++i) { g[i].clear(); }
        for(int i = 1; i <= n; ++i) { std::cin >> g_has_bed[i]; }
        for(int i = 1; i <= n; ++i) { std::cin >> g_need_bed[i]; g_need_bed[i] = !(g_need_bed[i] && g_has_bed[i]); }
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                std::cin >> flag_tmp;
                if(g_need_bed[i] == 1 && g_has_bed[j] == 1 && (flag_tmp == 1 || i == j)) { g[i].push_back(j); }
            }
        }
        for(int u = 1; u <= n; ++u) {
            if(g_need_bed[u] == 0) { continue; }
            std::fill(g_vis + 1, g_vis + 1 + n, false);
            ans += dfs(u);
        }
        std::cout << (ans >= std::accumulate(g_need_bed + 1, g_need_bed + 1 + n, 0) ? "^_^" : "T_T") << '\n';
    }
}
```

#### 二分图最大独立集

**二分图最大独立集本质上研究的是“独立关系”（点）的最大数量，要求选出的点之间不能有边**。

> [洛谷P1129](https://www.luogu.com.cn/problem/P1129)：给定棋盘`bool map[1->n<=100][1->n<=100]`，其中`map[i][j] = std::gcd(i, j) > 1`，若为`true`则表示该处`(i, j)`必须被木块覆盖。现有无限个尺寸为`2×1`的木块，木块之间**允许重叠**，请问棋盘上需至少摆放多少木块，才能覆盖所有必需被覆盖的格子？

本题需要逆向思维：一个木块最高效的摆放方法肯定是同时覆盖两个`true`格子。于是在最坏情况下，每个`true`格子都单独需要一个木块，但凡存在相邻`true`格子，就可以在这两个相邻的、奇偶性相反的`true`格子之间建立匹配，每匹配一次，所需要的木块数量就减`1`。于是可以认为黑`true`块与白`true`块分别构成了两个子图，若黑白`true`之间相邻，则存在一条无向边，问题转化为求解`true`块的总数量减去二部图最大匹配的大小。

本题另一个棘手的地方在于，如何快速计算每个格子的`map[i][j]`。容易想到一种朴素的算法：每个格子计算一次`std::gcd()`，时间复杂度为$O(n^2\log_2{n})$。实际上，我们可以直接枚举因数`d∈[2, n]`，内层的`(i, j)`分别每隔`d`就枚举一次，因此时间复杂度为$O\left(\displaystyle\sum_{d=2}^{n}\left(\frac{n}{d}\right)^2\right) = O\left(n^2\displaystyle\sum_{d=2}^{n}\frac{1}{d^2}\right) \le O\left(n^2\cdot\displaystyle\frac{\pi^2}{6}\right) \approx O(n^2)$。

```c++
const int N_MAX = 233, DIR[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, ans; bool map[1 + N_MAX][1 + N_MAX];
std::map<int, std::vector<int>> g; std::map<int, bool> vis; std::map<int, int> match;

inline int get_index(int i, int j) { return i * n + j; }
bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v]) == true) {
            match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n;
    for(int d = 2; d <= n; ++d) { for(int i = d; i <= n; i += d) { for(int j = d; j <= n; j += d) { map[i][j] = true; } } }
    for(int i = 1; i <= n; ++i) { for(int j = 1; j <= n; ++j) { if(map[i][j] == true) { ++ans; } } }

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(map[i][j] == false || (i + j) % 2 == 0) { continue; }
            for(int p = 0; p < 4; ++p) {
                int i_new = i + DIR[p][0], j_new = j + DIR[p][1];
                if(i_new < 1 || i_new > n || j_new < 1 || j_new > n || map[i_new][j_new] == false) { continue; }
                g[get_index(i, j)].push_back(get_index(i_new, j_new));
            }
        }
    }

    for(auto& [u, _] : g) { vis.clear(); ans -= dfs(u); }
    std::cout << ans;
}
```

> [洛谷P4251](https://www.luogu.com.cn/problem/P4251)：给定矩阵`int map[1->n<=250][1->m<=250]`，从中选出`n`个数字，保证两两不在同一行和同一列。求这`n`个数字中第`k`大数字的最小值。

本题二部图建图方式显然：行列分别视为一个子图，每次选中一个`(i, j)`坐标的数字，就在第`i`行与第`j`列之间建一条无向边。如果对所有格子建边，则注意到此时没有任何约束条件，二部图最大匹配的大小显然为`std::min(n, m)`。

不妨考虑二分搜索，转化为判定性问题。注意到本题求的是**第`k`大**的数字，因此前`1->k-1`大的数字无需考虑，只需考虑后`n-k+1`个数字即可，因为二部图最大匹配的大小保证了**前`k`大**的数字一定能构成匹配。问题转化为：**给定`map[i][j] <= ans`的子图**，在保证其二部图最大匹配的大小`>= n-k+1`的前提下，`ans`的最小值是多少。**其中`ans`是第`k`大数字的最小值，约束着后面`n-k+1`个数字的大小**。

```c++
const int N_MAX = 250, M_MAX = 250;
int n, m, k, map[1 + N_MAX][1 + M_MAX], map_v[1 + N_MAX * M_MAX], map_v_cnt;

std::vector<int> g[1 + N_MAX]; int g_match[1 + M_MAX]; bool g_vis[1 + M_MAX];
bool dfs(int u) {
    for(int v : g[u]) {
        if(g_vis[v] == true) { continue; } g_vis[v] = true;
        if(g_match[v] == 0 || dfs(g_match[v]) == true) {
            g_match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n >> m >> k;
    for(int i = 1; i <= n; ++i) { for(int j = 1; j <= m; ++j) { std::cin >> map[i][j]; map_v[++map_v_cnt] = map[i][j]; } }
    std::sort(map_v + 1, map_v + 1 + n * m);

    int l = 1, r = n * m - (k - 1);
    while(l <= r) {
        for(int i = 1; i <= n; ++i) { g[i].clear(); }
        std::fill(g_match + 1, g_match + 1 + m, false);
        
        int mid = (l + r) / 2, ans = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(map[i][j] > map_v[mid]) { continue; }
                g[i].push_back(j);
            }
        }
        for(int u = 1; u <= n; ++u) {
            std::fill(g_vis + 1, g_vis + 1 + m, false);
            ans += dfs(u);
        }
        if(ans >= n - k + 1) { // 随着mid的增大, check()返回值从false变为true
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    std::cout << map_v[l];
}
```

> [洛谷P5030](https://www.luogu.com.cn/problem/P5030)：给定尺寸为`n×m<=200×200`的格子棋盘，以及`k`个不可用的格子坐标。一个士兵可以攻击`const int DIR[8][2] = {{1, 3}, {3, 1}, {3, -1}, {1, -3}, {-1, -3}, {-3, -1}, {-3, 1}, {-1, 3}}`这八个相邻位置的格子。若棋盘上的所有士兵都无法相互攻击，求士兵数量的最大值。

本题可以用二部图匹配来做：
- 若两个格子之间能相互攻击则说明存在一条无序边，因此问题转化为从图中选择尽可能多的点，保证点与点之间不存在任何边。这是一个最大独立集问题。
- **难点在于如何确定二部图的左右两个子图**。注意到棋子在做一次移动时，一定会同时改变行坐标和列坐标的奇偶性。于是不妨只考虑行坐标的奇偶性变化，在一步之内，位于第`i`行的士兵肯定不会跳到第`i±2`行，也就是说奇偶性相同的行内格子无法相互攻击，因此可以作为一个子图。于是根据行号的奇偶性可以划分为两个子图。如果一个格子`(i, j)`能攻击到另一个格子`(i_new, j_new)`，则这两个格子之间存在一条无向边，表示二者最多只能留其一。

此处考虑逆推：起初棋盘上的每个合法格子都摆放一个士兵（总数为`n * m - k`），匹配数每增加`1`，就说明有两个士兵发生了冲突，因此答案要减`1`。最后输出`n * m - 去重后的k - ans`即可。

```c++
const int N_MAX = 200, M_MAX = 200, DIR[8][2] = {{1, 3}, {3, 1}, {3, -1}, {1, -3}, {-1, -3}, {-3, -1}, {-3, 1}, {-1, 3}};
int n, m, k, x_tmp, y_tmp, ans; std::set<std::pair<int, int>> set;
inline int get_index(int x, int y) { return m * (x - 1) + (y - 1) + 1; }

std::vector<int> g[1 + N_MAX * M_MAX]; int match[1 + N_MAX * M_MAX]; bool vis[1 + N_MAX * M_MAX];
bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v]) == true) {
            match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n >> m >> k;
    for(int i = 1; i <= k; ++i) { std::cin >> x_tmp >> y_tmp; set.emplace(x_tmp, y_tmp); }

    for(int i = 1; i <= n; i += 2) { // 只从左子图开始遍历，创建无向边
        for(int j = 1; j <= m; ++j) {
            if(set.count({i, j}) >= 1) { continue; }
            for(int p = 0; p < 8; ++p) {
                int i_new = i + DIR[p][0], j_new = j + DIR[p][1];
                if(i_new < 1 || i_new > n || j_new < 1 || j_new > m || set.count({i_new, j_new}) >= 1) { continue; }
                g[get_index(i, j)].emplace_back(get_index(i_new, j_new));
            }
        }
    }

    for(int i = 1; i <= n; i += 2) { // 只遍历左子图的n1个节点
        for(int j = 1; j <= m; ++j) {
            std::fill(vis + 1, vis + 1 + n * m, false);
            ans += dfs(get_index(i, j));
        }
    }
    std::cout << n * m - set.size() - ans;
}
```

> [洛谷P3882](https://www.luogu.com.cn/problem/P3882)：给定尺寸为`n×m<=1024×1024`的格子棋盘，按照`char map[1->n][1->m]`摆放棋子：（1）国王`K`可以攻击周围相邻`8`个格子；（2）皇后`Q`攻击同一行、同一列、同一对角线的格子，攻击范围会被已有棋子阻挡；（3）士兵`B`攻击同一对角线的格子，攻击范围会被已有棋子阻挡；（4）骑士`K`：类似于中国象棋的马，攻击`8`个格子；（5）车`R`攻击同一行、同一列的格子，攻击范围会被已有棋子阻挡；（6）步兵`P`攻击同一对角线中沿`n`方向递增的格子，攻击范围会被已有棋子阻挡；（7）空白格子`.`。现在请在空白格子的位置，摆放尽可能多的士兵`B`，保证**新放置**的士兵`B`不会互相攻击，也不会被已有棋子攻击。不考虑**原有**棋子相互攻击的情况。

令`bool valid_grid[1->n][1->m]`表示本处格子是否空闲，即`map[i][j] == '.'`。

本题可以用二部图匹配来做：
- **难点在于如何确定二部图的左右两个子图**。注意到每次放一个教主，主副对角线就会被占用，不妨使用`x = i + j ∈[2,n+m]`与`y = i - j ∈[1-m,n-1]`的值来表示主对角线与副对角线。于是一个教主的位置可以由`(x, y)`唯一确定，**不妨将其记为一定从顶点`x`到顶点`y`的无向边**。这样可以保证`x_1, x_2, ...`之间一定不存在边，`y_1, y_2, ...`之间同样一定不存在边，而`(x, y)`之间可能存在一条边。
- 建边时，对于每个可选的空白格子`(i, j)`，为对应的`(x, y)`建立一条无向边即可。

至此，问题转化为了求二部图最大匹配。

```c++
const int N_MAX = 1024, M_MAX = 1024, G1_MAX = N_MAX + M_MAX - 1, DIR_KING[8][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}}, DIR_KNIGHT[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
int n, m, ans; char map[1 + N_MAX][1 + M_MAX]; bool valid_grid[1 + N_MAX][1 + M_MAX], valid_diag[2][1 + G1_MAX];

inline int get_x_index(int i, int j) { return i + j - 1; } // ∈ [2, n + m + 2] -> [1, n + m - 1]
inline int get_y_index(int i, int j) { return i - j + m; } // ∈ [1 - m, n - 1] -> [1, n + m - 1]
inline void disable_valid_grid(int i, int j) { if(i < 1 || i > n || j < 1 || j > m) { return; } valid_grid[i][j] = false; }
inline void disable_valid_diag(int i, int j) { if(i < 1 || i > n || j < 1 || j > m) { return; } valid_diag[0][get_x_index(i, j)] = false; valid_diag[1][get_y_index(i, j)] = false; }

std::vector<int> g[1 + G1_MAX]; int match[1 + G1_MAX]; bool vis[1 + G1_MAX];
bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v]) == true) {
            match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n >> m;
    for(int i = 1; i <= n; ++i) { for(int j = 1; j <= m; ++j) { std::cin >> map[i][j]; valid_grid[i][j] = (map[i][j] == '.'); } }

    std::fill(&(valid_diag[0][0]), &(valid_diag[1][G1_MAX]) + 1, true);
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            if(map[i][j] == '.') { continue; } disable_valid_diag(i, j);
            if(map[i][j] == 'K') { 
                for(int p = 0; p < 8; ++p) { disable_valid_grid(i + DIR_KING[p][0], j + DIR_KING[p][1]); } 
            } else if(map[i][j] == 'Q') {
                for(int i_new = i + 1; i_new <= n; ++i_new) { if(map[i_new][j] != '.') { break; } disable_valid_grid(i_new, j); }
                for(int i_new = i - 1; i_new >= 1; --i_new) { if(map[i_new][j] != '.') { break; } disable_valid_grid(i_new, j); }
                for(int j_new = j + 1; j_new <= m; ++j_new) { if(map[i][j_new] != '.') { break; } disable_valid_grid(i, j_new); }
                for(int j_new = j - 1; j_new >= 1; --j_new) { if(map[i][j_new] != '.') { break; } disable_valid_grid(i, j_new); }
                for(int i_new = i + 1; i_new <= std::min(n, i + j - 1); ++i_new) { if(map[i_new][i + j - i_new] != '.') { break; } disable_valid_grid(i_new, i + j - i_new); }
                for(int i_new = i - 1; i_new >= std::max(1, i + j - m); --i_new) { if(map[i_new][i + j - i_new] != '.') { break; } disable_valid_grid(i_new, i + j - i_new); }
                for(int i_new = i + 1; i_new <= std::min(n, m + i - j); ++i_new) { if(map[i_new][i_new - (i - j)] != '.') { break; } disable_valid_grid(i_new, i_new - (i - j)); }
                for(int i_new = i - 1; i_new >= std::max(1, 1 + i - j); ++i_new) { if(map[i_new][i_new - (i - j)] != '.') { break; } disable_valid_grid(i_new, i_new - (i - j)); }

            } else if(map[i][j] == 'B') {
                for(int i_new = i + 1; i_new <= std::min(n, i + j - 1); ++i_new) { if(map[i_new][i + j - i_new] != '.') { break; } disable_valid_grid(i_new, i + j - i_new); }
                for(int i_new = i - 1; i_new >= std::max(1, i + j - m); --i_new) { if(map[i_new][i + j - i_new] != '.') { break; } disable_valid_grid(i_new, i + j - i_new); }
                for(int i_new = i + 1; i_new <= std::min(n, m + i - j); ++i_new) { if(map[i_new][i_new - (i - j)] != '.') { break; } disable_valid_grid(i_new, i_new - (i - j)); }
                for(int i_new = i - 1; i_new >= std::max(1, 1 + i - j); ++i_new) { if(map[i_new][i_new - (i - j)] != '.') { break; } disable_valid_grid(i_new, i_new - (i - j)); }
            } else if(map[i][j] == 'N') {
                for(int p = 0; p < 8; ++p) { disable_valid_grid(i + DIR_KNIGHT[p][0], j + DIR_KNIGHT[p][1]); } 
            } else if(map[i][j] == 'R') {
                for(int i_new = i + 1; i_new <= n; ++i_new) { if(map[i_new][j] != '.') { break; } disable_valid_grid(i_new, j); }
                for(int i_new = i - 1; i_new >= 1; --i_new) { if(map[i_new][j] != '.') { break; } disable_valid_grid(i_new, j); }
                for(int j_new = j + 1; j_new <= m; ++j_new) { if(map[i][j_new] != '.') { break; } disable_valid_grid(i, j_new); }
                for(int j_new = j - 1; j_new >= 1; --j_new) { if(map[i][j_new] != '.') { break; } disable_valid_grid(i, j_new); }
            } else if(map[i][j] == 'P') {
                disable_valid_grid(i + 1, j - 1); disable_valid_grid(i + 1, j + 1);
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            int x = get_x_index(i, j), y = get_y_index(i, j);
            if(valid_grid[i][j] == false || valid_diag[0][x] == false || valid_diag[1][y] == false) { continue; }
            g[x].push_back(y);
        }
    }
    for(int u = 1; u <= n + m - 1; ++u) {
        std::fill(vis + 1, vis + 1 + (n + m - 1), false);
        ans += dfs(u);
    }
    std::cout << ans;
}
```

> [洛谷P5030](https://www.luogu.com.cn/problem/P5030)：给定`n<=250`条水平线段或垂直线段，其端点坐标由`struct Seg { int x1, y1, x2, y2 };`给出。现需从中选出若干条线段，并且保证线段之间不存在两两相交（包含端点重合）的情况，则线段数量的最大值是多少？

将水平线段、垂直线段分别作为左右子图，跑一遍二分图最大独立集即可。由于`n<=250`，所以可以直接暴力$O(n^2)$进行建边。

```c++
const int N_MAX = 250;
int n, x1_tmp, y1_tmp, x2_tmp, y2_tmp, ans; bool type_tmp;
struct Seg { int x1, y1, x2, y2; } seg[2][1 + N_MAX]; int seg_cnt[2]; // 0/false表示行, 1/true表示列
inline bool check_type(int x1, int y1, int x2, int y2) { return x1 == x2; }
inline bool check_cross(Seg &line, Seg &col) { return (line.x1 <= col.x1) && (col.x1 <= line.x2) && (col.y1 <= line.y1) && (line.y1 <= col.y2); }

std::vector<int> g[1 + N_MAX]; int match[1 + N_MAX]; bool vis[1 + N_MAX];
bool dfs(int u) {
    for(int v : g[u]) {
        if(vis[v] == true) { continue; } vis[v] = true;
        if(match[v] == 0 || dfs(match[v]) == true) {
            match[v] = u; return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n;
    for(int i = 1; i <= n; ++i) {
        std::cin >> x1_tmp >> y1_tmp >> x2_tmp >> y2_tmp; type_tmp = check_type(x1_tmp,y1_tmp, x2_tmp, y2_tmp);
        if(type_tmp == false && x1_tmp > x2_tmp) { std::swap(x1_tmp, x2_tmp); }
        if(type_tmp == true && y1_tmp > y2_tmp) { std::swap(y1_tmp, y2_tmp); }
        seg[type_tmp][++seg_cnt[type_tmp]] = {.x1 = x1_tmp, .y1 = y1_tmp, .x2 = x2_tmp, .y2 = y2_tmp};
    }

    for(int i = 1; i <= seg_cnt[0]; ++i) {
        for(int j = 1; j <= seg_cnt[1]; ++j) {
            if(check_cross(seg[0][i], seg[1][j]) == false) { continue; }
            g[i].push_back(j);
        }
    }

    for(int u = 1; u <= seg_cnt[0]; ++u) {
        std::fill(vis + 1, vis + 1 + seg_cnt[1], false);
        ans += dfs(u);
    }
    std::cout << n - ans;
}
```

#### 网络最大流

> [洛谷P3376](https://www.luogu.com.cn/problem/P3376)：网络最大流模版题。给定包含`n<=200`个点、`m<=5e3`条边的带权(`w[]<=INT32_MAX`)有向图，求从起点`s`到终点`t`的网络最大流。

这里我们采用最佳的Dinic算法：

1. 建图时，同时添加正向带权有向边`<u, v, c>`、反向带权有向边`<v, u, 0>`。
2. 重复以下循环，每次执行BFS生成新的`g_level[*]`，直到不存在从起点s到终点t依然有余量大于`0`的路径为止。在每个循环内：
	1. 清空`g_cur[*]`，供后续DFS对边进行剪枝。
	2. 反复调用DFS，每次调用都能返回新发现的增广路径$P=\{e_1. e_2, \cdots\}$带来的最大流增长量$\Delta \mathrm{ans}= \min(w_{e_1}, w_{e_2}, \cdots)$，直到DFS返回`0`为止。
		1. 每次调用DFS时，必须保证发现的增广路径满足：通过BFS序保证路径最短的（`g_layer[v] == g_layer[u] + 1`）、路径上各个边的边权均大于`0`（`edge[i].c > 0`）。
		2. 对于发现的增广路径$P=\{e_1. e_2, \cdots\}$，首先对于其中的边执行`e[i].c -= Δans`。然后取其反向边构成的反向增广路径$\hat P = \{\hat e_1, \hat e_2, \cdots\}$，执行`ê[i].c += Δans`。
3. 将最大流增长量全部相加，就得到了最终答案。

为了保证BFS/DFS搜索到的路径，可以保证路径上的所有边的边权最小值大于`0`，在代码实现时可以忽略所有边权为`0`的边。

| 变量名                             | 含义                                                       | 注意事项                                                   |
| ------------------------------- | -------------------------------------------------------- | ------------------------------------------------------ |
| `std::vector<int> g[1 + N_MAX]` | 顶点`u`对应的有向边邻接表，即`g[u]`                                   | 受制于`std::vector`的实现，`g[u][*]`的下标从`0`开始                 |
| `int g_cnt[1 + N_MAX]`          | 顶点`u`对应的有向边邻接表的元素数量，即`g[u].size()`                       |                                                        |
| `int g_cur[1 + N_MAX]`          | 顶点`u`对应的有向边邻接表，目前要遍历的边的序号，即下一步需要遍历`edge[g[u][g_cur[u]]]` | 受制于`std::vector`的实现，`g[u][*]`的值从`0`开始，小于`g_cnt[u]`     |
| `int g_layer[1 + N_MAX]`        | 顶点`u`对应的BFS层号                                            | 起点`s`满足`g_layer[s] == 0`，不可达的点的`u`满足`g_layer[u] == -1` |

分析该算法的时间复杂度：
- 对于外层`bfs()`循环，每循环一次的BFS开销为$O(n+m)$，而且都能保证目前所有从起点`s`到终点`t`的最短路径都会被内层的`dfs()`循环干掉，因此最短路径长度严格递增，最坏情况下每次递增`+1`，最长为`n`本身，于是外层需要循环$O(n)$次。
- 对于内层`dfs()`循环，由于已经生成了全局的BFS序`g_layer[*]`，因此不妨把所有DFS放在一起考虑。由于一次DFS至少保证一条正向带权有向边的余量`c`被耗尽为`0`，切后续的DFS会跳过这类边，因此余量永远不会恢复，显然最坏情况下会产生$O(m)$条增广路径。一条增广路径最多有$n-1\approx O(n)$条边，每条边都需要更新，因此更新一条增广路径的时间复杂度是$O(n)$。综上所述，内层DFS循环的时间复杂度是$O(nm)$。
综上所述，总的时间复杂度是$O(n((n+m)+nm))\approx O(n^2 m)$。

```c++
const int N_MAX = 200, M_MAX = 5000;
int n, m, s, t, u_tmp, v_tmp; int64_t c_tmp, ans, ans_tmp;
struct Edge { int v; int64_t c; int i_inv; } edge[1 + M_MAX * 2]; int edge_count;
std::vector<int> g[1 + N_MAX]; int g_cnt[1 + N_MAX], g_cur[1 + N_MAX], g_level[1 + N_MAX];
// g[u][0->g_cnt[u]-1]，下表从0开始

inline bool bfs(int s) {
    std::fill(g_level + 1, g_level + 1 + n, -1); g_level[s] = 0;
    std::queue<int> q; q.push(s);
    while(q.empty() == false) {
        int u = q.front(); q.pop();
        for(int i : g[u]) {
            auto &[v, c, i_inv] = edge[i];
            if(c <= 0 || g_level[v] != -1) { continue; }
            g_level[v] = g_level[u] + 1; q.push(v);
        }
    }
    return g_level[t] != -1;
}
int64_t dfs(int u, int64_t c_max) {
    if(u == t) { return c_max; }
    for(int &p = g_cur[u]; p < g_cnt[u]; ++p) { // 保证edge[g[u][0->p-1]]范围内的边e一定失去了遍历价值，例如e.c<=0或g_level[v]!=g_level[u]+1，因此直接遍历剩余的edge[g[u][p->g_cnt[u]-1]]即可
        int &i = g[u][p]; auto &[v, c, i_inv] = edge[i];
        if(c <= 0 || g_level[v] != g_level[u] + 1) { continue; }
        if((ans_tmp = dfs(v, std::min(c_max, c))) > 0) {
            edge[i].c -= ans_tmp; edge[i_inv].c += ans_tmp;
            return ans_tmp; // 此处无需++p，因为此时edge[i].c仍然可能大于0，依然有遍历价值
        }
    }
    return 0;
}

int main() {
    std::cin >> n >> m >> s >> t;
    for(int i = 1; i <= m; ++i) {
        std::cin >> u_tmp >> v_tmp >> c_tmp;
        ++edge_count; edge[edge_count] = {.v = v_tmp, .c = c_tmp, .i_inv = edge_count + 1}; g[u_tmp].push_back(edge_count); ++g_cnt[u_tmp];
        ++edge_count; edge[edge_count] = {.v = u_tmp, .c = 0, .i_inv = edge_count - 1}; g[v_tmp].push_back(edge_count); ++g_cnt[v_tmp];
    }

    while(bfs(s) == true) {
        std::fill(g_cur + 1, g_cur + 1 + n, 0);
        while((ans_tmp = dfs(s, INT64_MAX)) > 0) { ans += ans_tmp; }
    }
    std::cout << ans;
}
```

> [洛谷P1402](https://www.luogu.com.cn/problem/P1402)：三部图最大匹配模版题。给定`n1<=100`个顾客、`n2<=100`个房间、`n3<=100`个菜谱。`bool c1[1->n1][n2], c2[1->n1][1->n3]`分别表示顾客对房间和菜谱的喜爱程度，只有当两个条件均满足时，才能让顾客感到满意。顾客、房间、菜谱三者匹配时只能一一对应，求感到满意的顾客数量最大值。

本题的棘手之处在于一个`n1`点，可以分别向`n2`点和`n3`点连边，导致一个`n1`点必须有两条相邻边。为了避免这种情况，我们将一个`n1`拆成两个相连的影子分身，分别向`n2`点和`n3`点连边，即可转化为最大流匹配问题。具体来说，从源点出发到达`n2`点，通过`c1[1->n1][1->n2]`映射到`n1_l`点，通过影子分身映射到`n1_r`点，通过`c2[1->n1][1->n3]`映射到`n3`点，统一汇总到终点。每个边权设置为`1`。

```c++
const int N1_MAX = 100, N2_MAX = 100, N3_MAX = 100, N_MAX = 1 + N2_MAX + N1_MAX * 2 + N3_MAX + 1, M_MAX = N2_MAX + N1_MAX * N2_MAX + N1_MAX + N1_MAX * N3_MAX + N3_MAX;
int n1, n2, n3, n, c_tmp, ans, ans_tmp;
std::vector<int> g[1 + N_MAX]; int g_cnt[1 + N_MAX], g_cur[1 + N_MAX], g_level[1 + N_MAX];
struct Edge { int v, c, i_inv; } edge[1 + M_MAX * 2]; int edge_count;
inline void edge_add(int u, int v) {
    ++edge_count; edge[edge_count] = {.v = v, .c = 1, .i_inv = edge_count + 1}; g[u].push_back(edge_count); ++g_cnt[u];
    ++edge_count; edge[edge_count] = {.v = u, .c = 0, .i_inv = edge_count - 1}; g[v].push_back(edge_count); ++g_cnt[v];
}
inline int get_s_index() { return 1; }
inline int get_n2_index(int i) { return 1 + i; }
inline int get_n1_l_index(int i) { return 1 + n2 + i; }
inline int get_n1_r_index(int i) { return 1 + n2 + n1 + i; }
inline int get_n3_index(int i) { return 1 + n2 + 2 * n1 + i; }
inline int get_e_index() { return 1 + n2 + n1 * 2 + n3 + 1; }

inline bool bfs(int s) {
    std::fill(g_level + 1, g_level + 1 + n, -1); g_level[s] = 0;
    std::queue<int> q; q.push(s);
    while(q.empty() == false) {
        int u = q.front(); q.pop();
        for(int i : g[u]) {
            auto &[v, c, i_inv] = edge[i];
            if(c <= 0 || g_level[v] != -1) { continue; }
            g_level[v] = g_level[u] + 1; q.push(v);
        }
    }
    return g_level[get_e_index()] != -1;
}
int dfs(int u, int c_max) {
    if(u == get_e_index()) { return c_max; }
    for(int &p = g_cur[u]; p < g_cnt[u]; ++p) {
        int &i = g[u][p]; auto &[v, c, i_inv] = edge[i];
        if(c <= 0 || g_level[v] != g_level[u] + 1) { continue; }
        if((ans_tmp = dfs(v, std::min(c_max, c))) > 0) {
            edge[i].c -= ans_tmp; edge[i_inv].c += ans_tmp;
            return ans_tmp;
        }
    }
    return 0;
}

int main() {
    std::cin >> n1 >> n2 >> n3; n = 1 + n2 + 2 * n1 + n3 + 1;

    for(int j = 1; j <= n2; ++j) { edge_add(get_s_index(), get_n2_index(j)); }
    for(int i = 1; i <= n1; ++i) { for(int j = 1; j <= n2; ++j) { std::cin >> c_tmp; if(c_tmp == 1) { edge_add(get_n2_index(j), get_n1_l_index(i)); } } }
    for(int i = 1; i <= n1; ++i) { edge_add(get_n1_l_index(i), get_n1_r_index(i)); }
    for(int i = 1; i <= n1; ++i) { for(int j = 1; j <= n3; ++j) { std::cin >> c_tmp; if(c_tmp == 1) { edge_add(get_n1_r_index(i), get_n3_index(j)); } } }
    for(int j = 1; j <= n3; ++j) { edge_add(get_n3_index(j), get_e_index()); }

    while(bfs(get_s_index()) == true) {
        std::fill(g_cur + 1, g_cur + 1 + n, 0);
        while((ans_tmp = dfs(get_s_index(), 1)) > 0) { ans += ans_tmp; }
    }
    std::cout << ans;
}
```