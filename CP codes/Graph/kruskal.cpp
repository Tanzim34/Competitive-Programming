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

struct Edge
{
	int u,v,weight;
	bool operator<(Edge const& other) {
       return weight < other.weight;
    }
};

vector<Edge> result;
vector<Edge> edges;

int Kruskal(int n)
{
	parent.resize(n+1);
	Rank.resize(n+1);
	int cost = 0;
	for(int i=0; i<n; i++) make_set(i);
	sort(edges.begin(),edges.end());
	
	for(Edge e : edges)
	{
		if(find_set(e.u)!=find_set(e.v)){
			cost+=e.weight;
			result.push_back(e);
			union_set(e.u,e.v);
		}
	}
	return cost;	
}