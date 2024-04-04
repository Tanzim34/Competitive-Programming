vector<vector<int>> adj(100009);
vector<bool> vis(100009);
vector<int> parent(100009);
vector<int> time_in(100001),time_out(100001);
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
	time_out[v] = timer++;

}