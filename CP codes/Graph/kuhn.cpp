int n = 102, ans = 0;
vector<vector<int>> e(n+1);
vector<bool> used(n+1);
vector<int> mt(n+1);

bool try_kuhn(int v)
{
	if(used[v]) return false;
	//ans++;
	used[v] = true;
	for(int to : e[v])
	{
		if(mt[to]==-1 || try_kuhn(mt[to])){
			mt[to] = v;
			//ans++;
			return true;
		}
	}
	return false;
}