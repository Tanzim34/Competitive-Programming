const long long  inf = 1e18;
int N = 1000001;
typedef long long ll;
vector<vector<pair<int,ll>>> adj(N+1);
vector<bool> used(N+1,false);
vector<int> p(N+1,-1);
vector<ll> d(N+1,inf);

void dijkstra(int s)
{
	d.assign(N+1,inf);
	p.assign(N+1,-1);
	priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
	d[s] = 0;
	q.push({0,s});

	while(!q.empty())
	{
		ll d_v = q.top().first;
		int v = q.top().second;
		q.pop();
		if(d_v!=d[v]) continue;

		for(auto edge: adj[v])
		{
			int u = edge.first;
			ll len = edge.second;

			if(d[v]+len < d[u])
			{
				d[u] = d[v]+len;
				p[u] = v;
				q.push({d[u],u});
			}
		}
	}
}