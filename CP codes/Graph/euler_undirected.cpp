#include<bits/stdc++.h>
// #include<ext/pb_ds/assoc_container.hpp>
// #include<ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
using namespace std;

// template <typename T> using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// template <typename T, typename R> using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long

// #pragma once
#pragma GCC optimize("O3")
#pragma GCC target("avx2")

typedef long long ll;
#define ld long double
const ll mod = 1e9 + 7;
const ll inf = 1e18 + 7;
const int N = 500005, M = 20;
// const int inf = 1e18 + 7;
const ld pi = acos(-1);

vector<pair<int,int>> adj[N];
vector<bool> vis(N, false);
int done[N];
vector<int> ans;

void dfs(int v){
    while(done[v] < adj[v].size()){
        auto a = adj[v][done[v]++];
        if(vis[a.second]) continue;
        vis[a.second] = 1;
        dfs(a.first);
        ans.push_back(a.second);
    }
}


int32_t main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tt = 1;
    cin >> tt;

    for(int tc=1; tc<=tt; tc++){
        
        // cout << "Case " << tc << ": ";

        int n;
        cin >> n;

        for(int i=1; i<=2*n; i++) adj[i].clear();

        map<int,int> mp1, mp2;
        pair<int, int> ara[n+1];
        int c1 = 0, c2 = 0;

        for(int i=1; i<=n; i++){
            int a, b;
            cin >> a >> b;
            ara[i] = {a, b};
            if(!mp1[a]) mp1[a] = ++c1;
            if(!mp2[b]) mp2[b] = ++c2;
        }

        vis.assign(n+2, false);
        ans.clear();

        for(int i=1; i<=n; i++){
            int u, v;
            u = mp1[ara[i].first], v = mp2[ara[i].second] + n;
            adj[u].push_back({v, i});
            adj[v].push_back({u, i});
        }

        int st = -1, c = 0, en = -1;
        for(int i=1; i<=2*n; i++){
            if(adj[i].size() & 1){
                c++;
                if(st == -1) st = i;
                else en = i;
            }
            done[i] = 0;
        }

        if(c > 2){
            cout << "NO\n";
            continue;
        }

        if(c == 2){
            adj[st].push_back({en, n+1});
            adj[en].push_back({st, n+1});
        }

        if(st != -1) dfs(st);
        else dfs(1);

        if((ans.size() != n && !c) || (ans.size() != n+1 && c)){
            cout << "NO\n";
            continue;
        } 

        reverse(ans.begin(), ans.end());

        cout << "YES\n";
        if(c == 2){
            int pos = -1;
            for(int i=0; i<ans.size(); i++){
                if(ans[i] == n+1) pos = i;
            }
            for(int i=pos+1; i<ans.size(); i++) cout << ans[i] << ' ';
            for(int i=0; i<pos; i++) cout << ans[i] << " ";
        }
        else for(auto a : ans) cout << a << " ";
        cout << '\n';

    }


    return 0;
        
}