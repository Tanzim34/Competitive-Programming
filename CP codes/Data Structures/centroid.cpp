int n,m,l, cnt;

vector<vector<int>> adj(N);
vector<int> par(N,-1);
vector<int> sz(N,0);
vector<bool> vis(N,false);
vector<int> ans(N,1000000);

int find_centroid(int v, int p, int n) {
  for (int x: adj[v]) {
    if (x != p) {
      if (!vis[x] && sz[x] > n / 2) {
        return find_centroid(x, v, n);
      }
    }
  }

  return v;
}

int find_size(int v, int p = -1) {
  if (vis[v]) return 0;
  sz[v] = 1;

  for (int x: adj[v]) {
    if (x != p) {
      sz[v] += find_size(x, v);
    }
  }

  return sz[v];
}

void init_centroid(int v , int p = -1) {
  find_size(v);

  int c = find_centroid(v, -1, sz[v]);
  vis[c] = true;
  par[c] = p;

  for (int x: adj[c]) {
    if (!vis[x]) {
      init_centroid(x, c);
    }
  }
}

int timer = 0;
vector<int> tin(N), tout(N);
vector<int> d(N,0);
vector<vector<int>> up(N, vector<int>(20));

void dfs(int v, int p = -1)
{
	tin[v] = timer++;
	up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

	for(int u : adj[v])
	{
		if(u==p) continue;
		d[u] = d[v] + 1;
		dfs(u,v);
	}
	tout[v] = timer++;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n+1);
    tout.resize(n+1);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n+1, vector<int>(l + 1));
    dfs(root, root);
}

int dist(int u, int v)
{
	int r = lca(u,v);
	return d[u]+d[v]-2*d[r];
}

void init_tree(int n)
{
	for(int i=1; i<=n; i++) adj[i].clear();
	par.resize(n+1,-1);
	sz.resize(n+1,0);
	vis.assign(n+1,false);
	ans.assign(n+1,1000000);
	d.resize(n+1,0);	
}

void update_tree(int v)
{
	cnt = min(cnt, ans[v]);
	ans[v] = 0;
	int i = par[v];
	while(i!=-1)
	{
		cnt = min(cnt, ans[i] + dist(i,v));
		// cout << v << " " << i << " " << ans[i]+dist(i,v) << "\n";
		ans[i] = min(ans[i], dist(i,v));
		i = par[i];
	}
}
