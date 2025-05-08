vector<int> time_in(N),time_out(N),p(N,-1);
int timer = 0;
vector<vector<int>> up(N,vector<int>(18,-1));

void dfs(int v, int par=-1)
{
	time_in[v] = timer++;
	for(int u : adj[v])
	{
		if(u==par) continue;
		d[u] = d[v]+1;
		p[u] = v;
		dfs(u,v);
	}
	time_out[v] = timer++;
}

void binary_lifting(int n)
{
	for(int i=1; i<=n; i++) up[i][0] = p[i];
	for(int j=1; j<=17; j++)
	{
		for(int i=1; i<=n; i++)
			if(up[i][j-1]!=-1)
				up[i][j] = up[up[i][j-1]][j-1];
	}
}

int kth_ancestor(int node, int k)
{
	 for (int i = 17; ~i; --i) {
            if (k >> i & 1) {
                node = up[node][i];
                if (node == -1) {
                    break;
                }
            }
      }
      return node;
}