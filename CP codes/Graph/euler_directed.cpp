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
// const int N = 1000001, M = 20;
// const int inf = 1e18 + 7;
const ld pi = acos(-1);

const ll N = 500005;
vector<int> adj[N];
int ind[N], outd[N], done[N];
vector<int> ans;

void dfs(int v){
    while(done[v] < adj[v].size()){
        dfs(adj[v][done[v]++]);
    }
    ans.push_back(v);
}


int32_t main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int tt = 1;
    // cin >> tt;

    for(int tc=1; tc<=tt; tc++){
        
        // cout << "Case " << tc << ": ";

        int n;
        cin >> n;

        map<string, int> mp;
        int c = 0, ed = 0;

        for(int i=1; i<=n; i++){
            string s; cin >> s;
            string r = s.substr(0, 2);
            string t = s.substr(1, 2);

            if(!mp[r]) mp[r] = ++c;
            if(!mp[t]) mp[t] = ++c;

            adj[mp[r]].push_back(mp[t]);
            ed++;
            outd[mp[r]]++;
            ind[mp[t]]++;
        }

        string ara[c+1];
        for(auto a : mp) ara[a.second] = a.first;

        int posin = -1, posout = -1;
        bool ok = 1;
        for(int i=1; i<=c; i++){
            if(ind[i] == outd[i]) continue;
            if(ind[i] - outd[i] == 1){
                if(posin == -1) posin = i;
                else ok = 0;
            }
            else if(outd[i] - ind[i] == 1){
                if(posout == -1) posout = i;
                else ok = 0;
            }
            else ok = 0;
        }

        if(!ok){
            cout << "NO\n";
            continue;
        }

        if(posout == -1) dfs(1);
        else dfs(posout);

        if(ans.size() != ed + 1){
            cout << "NO\n";
            continue;
        }  
        reverse(ans.begin(), ans.end());
        
        cout << "YES\n";
        cout << ara[ans[0]];
        for(int i=1; i<ans.size(); i++) cout << ara[ans[i]].back();
        cout << '\n';

    }


    return 0;
        
}