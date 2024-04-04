vector<vector<int>> adj(100009);
vector<bool> vis(100009);
vector<int> parent(100009);
vector<int> time_in(100001),time_out(100001);
vector<int> ans;
int timer = 1;

void dfs(int v, int par = -1)
{
	vis[v] = true;
	time_in[v] = timer++;
	int child = 0;
	for(int u: adj[v])
	{
		if(u==par) continue;
		if(!vis[u])
		{
			parent[u] = v;
			dfs(u,v);
		}
	}
	ans.push_back(v);
	time_out[v] = timer++;

}

void top_sort(int n)
{
	vis.assign(n+1,false);
	ans.clear();
	for(int i=1; i<=n; i++)
	{
		if(!vis[i]) dfs(i);
	}
	reverse(ans.begin(),ans.end());
}