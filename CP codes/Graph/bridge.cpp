int timer = 1;
vector<pair<int,int>> bridge(100001);

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
			if(low[u]>time_in[v]){
				bridge.push_back({v,u});
			}
	}
	return ;
}

void bridges(int n)
{
	vis.assign(n+1,false);
	time_in.assign(n+1,-1);
	low.assign(n+1,10000000);

	for(int i=1; i<=n; i++){
		if(!vis[i]) dfs(i);
	} 

}