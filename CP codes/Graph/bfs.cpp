void bfs(int v)
{
	parent[v] = -1;
	vis[v] = true;
	q.push(v);
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int w: adj[u])
		{
			if(vis[w]==false){
				parent[w] = u;
				d[w] = d[u]+1;
				vis[w] = true;
				q.push(w);
			}
		}
	}
}
