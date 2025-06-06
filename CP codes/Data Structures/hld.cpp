const int N = 2e5 + 9, LG = 18, inf = 1e9 + 9;

int ara[N];

struct ST {
#define lc (n << 1)
#define rc ((n << 1) | 1)
  int t[4 * N], lazy[4 * N];
  ST() {
    fill(t, t + 4 * N, 0);
    fill(lazy, lazy + 4 * N, 0);
  }
  inline void push(int n, int b, int e) {
    if(lazy[n] == 0) return;
    t[n] = t[n] + lazy[n];
    if(b != e) {
      lazy[lc] = lazy[lc] + lazy[n];
      lazy[rc] = lazy[rc] + lazy[n];
    }
    lazy[n] = 0;
  }
  inline int combine(int a, int b) {
    return a + b; //merge left and right queries
  }
  inline void pull(int n) {
    t[n] = t[lc] +  t[rc]; //merge lower nodes of the tree to get the parent node
  }
  void build(int n, int b, int e) {
    if(b == e) {
      t[n] = ara[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(n);
  }
  void upd(int n, int b, int e, int i, int j, int v) {
    push(n, b, e);
    if(j < b || e < i) return;
    if(i <= b && e <= j) {
      lazy[n] += v;
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  int query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if(i > e || b > j) return 0;
    if(i <= b && e <= j) return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
} t;

vector<int> adj[N];
int par[N][LG + 1], dep[N], sz[N];
void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  if (p) adj[u].erase(find(adj[u].begin(), adj[u].end(), p));
  for (auto &v : adj[u]) if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if(sz[v] > sz[adj[u][0]]) swap(v, adj[u][0]);
    }
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int kth(int u, int k) {
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
  return u;
}
int T, head[N], st[N], en[N];
void dfs_hld(int u) {
  st[u] = ++T;
  for (auto v : adj[u]) {
    head[v] = (v == adj[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  en[u] = T;
}
int n;
int query_up(int u, int v) {
  int ans = 0;
  while(head[u] != head[v]) {
    ans = ans + t.query(1, 1, n, st[head[u]], st[u]);
    u = par[head[u]][0];
  }
  ans = ans + t.query(1, 1, n, st[v], st[u]);
  return ans;
}
int query(int u, int v) {
  int l = lca(u, v);
  int ans = query_up(u, l);
  if (v != l) ans += query_up(v, kth(v, dep[v] - dep[l] - 1));
  return ans;
}
void update_up(int u, int v, int val) {
  while (head[u] != head[v]) {
    t.upd(1, 1, n, st[head[u]], st[u], val);
    u = par[head[u]][0];
  }
  t.upd(1, 1, n, st[v], st[u], val);
}

//Add val to the vertices in path from u to v
void update(int u, int v, int val) {
  int l = lca(u, v);
  update_up(u, l, val);
  if (v != l) update_up(v, kth(v, dep[v] - dep[l] - 1), val);
}