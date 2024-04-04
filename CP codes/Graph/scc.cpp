vector<vector<int>> adj(100009), adj_rev(100009);
vector<bool> visited(100009,false);
vector<int> order,component;
//set<int> component;

void dfs1(int v)
{
	visited[v] = true;
	for(int u: adj[v])
	{
		if(!visited[u]) dfs1(u);
	}
	order.push_back(v);
}

void dfs2(int v)
{
	component.push_back(v);
	visited[v] = true;
	for(int u: adj_rev[v])
	{
		if(!visited[u]) dfs2(u);
	}
}