int idx = 0, euler[N], pos[N], sz[N], hc[N];

void dfs(int u, int p) {
  pos[u] = idx;
  euler[idx++] = u;
  sz[u] = 1, hc[u] = -1;
  for (auto v: adj[u]) {
    if (v == p)  continue;
    dfs(v, u);
    sz[u] += sz[v];
    if (hc[u] == -1 or sz[hc[u]] < sz[v]) {
      hc[u] = v;
    }
  }
}

int freq[N], cur_distinct = 0, distinct[N];

void add(int u) {
  freq[c[u]]++;
  if (freq[c[u]] == 1) {
    cur_distinct++;
  }
}

void remove(int u) {
  freq[c[u]]--;
  if (freq[c[u]] == 0) {
    cur_distinct--;
  }
}

void dsu(int u, int p, int keep) {
  for (int v: adj[u]) {
    if (v == p or v == hc[u])  continue;
    dsu(v, u, 0);
  }

  if (hc[u] != -1) {
    dsu(hc[u], u, 1);
  }

  for (auto v: adj[u]) {
    if (v == p or v == hc[u])  continue;
    for (int i = pos[v]; i < pos[v] + sz[v]; ++i) {
      int w = euler[i];
      add(w);
    }
  }

  add(u);
  distinct[u] = cur_distinct;

  if (!keep) {
    for (int i = pos[u]; i < pos[u] + sz[u]; ++i) {
      int w = euler[i];
      remove(w);
    }
  }
}