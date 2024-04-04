void dfs(int u, int p) {
  cols[u] = {c[u]};
  for (auto v: adj[u]) {
    if (v == p)  continue;
    dfs(v, u);
    if (cols[u].size() < cols[v].size()) {
      swap(cols[u], cols[v]);
    }
    for (auto x: cols[v]) {
      cols[u].insert(x);
    }
  }
  distinct[u] = cols[u].size();
}