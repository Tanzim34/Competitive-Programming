int N = 100000;
vector<int> parent(N),Rank(N);

void make_set(int v)
{
	parent[v] = v;
	Rank[v] = 0;
}

int find_set(int v){
	if(parent[v]==v) return v;
	return parent[v] = find_set(parent[v]);
}

void union_set(int u, int v)
{
	u = find_set(u);
	v = find_set(v);
	if(u!=v)
	{
		if(Rank[u]<Rank[v]) swap(u,v);
		parent[v] = u;
		if(Rank[u]==Rank[v]) Rank[u]++;
	}
}