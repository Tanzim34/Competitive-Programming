vector<pair<int,int>> adj[9*N];
int n;

void add_edge(int u, int v, int w = 0){
    adj[u].push_back({v, w});
}

void build(int v, int tl, int tr)
{
    if(tl==tr){
        add_edge(v + n, tl, 0);
        add_edge(tl , v + 5*n, 0);
        return;
    }
    else
    {
        int mid = (tl+tr)/2;
        add_edge(v + n, 2*v + n, 0);
        add_edge(v + n, 2*v + 1 + n, 0);
        add_edge(2*v + 1 + 5*n, v + 5*n, 0);
        add_edge(2*v + 5*n, v + 5*n, 0);

        build(2*v, tl, mid);
        build(2*v+1, mid+1, tr);
        
    }
}

//Update as - add edge from st to all vertex in the range [l, r]
void update(int v, int tl, int tr, int st, int i, int j, int w = 1)
{
    if(i>tr || j<tl) return;

    if(tl>=i && tr<=j){
        if(tl == tr){
            add_edge(st, tl, w);
        }
        else add_edge(st, v + n, w);
        return;
    }

    int mid = (tr+tl)/2;
    update(2*v, tl, mid, st, i, j, w);
    update(2*v + 1, mid+1, tr, st, i, j, w);

    return;
}

//Update as - add edge from all [l, r] to st
void inv_update(int v, int tl, int tr, int st, int i, int j, int w = 1)
{
    if(i>tr || j<tl) return;

    if(tl>=i && tr<=j){
        if(tl == tr) add_edge(tl, st, w);
        else add_edge(v + 5*n, st, w);
        return;
    }

    int mid = (tr+tl)/2;
    inv_update(2*v, tl, mid, st, i, j, w);
    inv_update(2*v + 1, mid+1, tr, st, i, j, w);

    return;
}

vector<bool> used(9*N+1,false);
vector<ll> d(9*N+1,inf);

void dijkstra(int s)
{
    d.assign(9*N+1,inf);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> q;
    d[s] = 0;
    q.push({0, s});

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
                q.push({d[u],u});
            }
        }
    }
}
