const int N_MAX = 6e3, M_MAX = 2 * N_MAX;
int edge_first[N_MAX + 1], edge_to[M_MAX + 1], edge_next[M_MAX + 1], edge_count;
inline void add_edge(int root, int child) {
    ++edge_count;
    edge_next[edge_count] = edge_first[root];
    edge_first[root] = edge_count;
    edge_to[edge_count] = child;
}
void dfs(int root, int father) {
    for(int i = edge_first[root]; i; i = edge_next[i]) {
        int child = edge_to[i];
        if(child == father) { continue; }
        dfs(child, root);
    }
}