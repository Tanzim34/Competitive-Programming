vector<vector<int>> adj(100009);
vector<bool> vis(100009,false);
vector<int> parent(100009,-1);
vector<int> time_in(100001), low(100001);
int timer = 1;
vector<int> cutpoints(100001);

void dfs(int v, int par = -1)
{
	vis[v] = true;
	time_in[v] = low[v] = timer++;
	int child = 0;
	for(int u: adj[v])
	{
		if(u==par) continue;
		if(vis[u])
		{
			low[v] = min(low[v],time_in[u]);
		}
		else
		{
			dfs(u,v);
			low[v] = min(low[v],low[u]);
			if(low[u]>=time_in[v] && par!=-1){
				cutpoints.push_back(v);
			}
			child++; 
		}
		if(par==-1 && child>1) cutpoints.push_back(v);
	}
	return ;
}

void find_cutpoints(int n)
{
	vis.assign(n+1,false);
	time_in.assign(n+1,-1);
	low.assign(n+1,10000000);

	for(int i=1; i<=n; i++){
		if(!vis[i]) dfs(i);
	} 

}