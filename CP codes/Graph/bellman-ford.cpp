int inf = 1000000000;

struct Edge{
	int u,v,cost;
};
vector<Edge> edges;
int N = 2500;
vector<int> d(N+1,inf);

void Bellman_Ford(int v)
{
	d[v] = 0;
	bool ok = false;
	while(1)
	{
		for(auto a : edges)
			if(d[a.u] < inf){
				if(d[a.v] > (d[a.u] + a.cost)){
					d[a.v] = d[a.u]+a.cost;
					ok = true;
				}
			}
		if(!ok) break;	
	}
}