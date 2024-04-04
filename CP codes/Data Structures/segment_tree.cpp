const int N = 200007;

ll t[4*N],ara[N+1];

void build(int v, int tl, int tr)
{
	if(tl==tr) t[v] = ara[tl];
	else
	{
		int mid = (tl+tr)/2;
		build(2*v,tl,mid);
		build(2*v+1,mid+1,tr);
		t[v] = t[2*v]+t[2*v+1];
	}
}

void update(int v, int tl, int tr, int pos, int val)
{
	if(tl==tr) t[v] = val;
	else
	{
		int mid = (tl+tr)/2;
		if(pos<=mid) update(2*v,tl,mid,pos,val);
		else update(2*v+1,mid+1,tr,pos,val);
		t[v] = t[2*v] + t[2*v+1];
	}
}

ll query(int v, int tl, int tr, int i, int j)
{
	if(i>tr || j<tl) return 0;

	if(tl>=i && tr<=j) return t[v];

	int mid = (tr+tl)/2;

	return query(2*v,tl,mid,i,j) + query(2*v+1,mid+1,tr,i,j);
}