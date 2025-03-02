    
    /*http://www.spoj.com/problems/ADAZOO/

    Steiner Tree : For a given weighted graph and a subset of k vertices, find the minimum spanning tree that
    includes all the k vertices   */

    int n;
    cin >> n;
    for(int i=0; i<n*n; i++) adj[i].clear();

    int h[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++) cin >> h[i][j];
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i!=0) adj[n*i+j].push_back({n*(i-1) + j, abs(h[i][j]-h[i-1][j])});
            if(i!=n-1) adj[n*i+j].push_back({n*(i+1) + j, abs(h[i][j]-h[i+1][j])});
            if(j!=0) adj[n*i+j].push_back({n*i + j-1, abs(h[i][j]-h[i][j-1])});
            if(j!=n-1) adj[n*i+j].push_back({n*i + j+1, abs(h[i][j]-h[i][j+1])});
        }
    }

    int q;
    cin >> q;
    vector<int> pt;
    for(int i=0; i<q; i++){
        int a,b;
        cin >> a >> b;
        pt.push_back(n*a + b);
    }

    ll dp[1<<q][n*n];
    for(int i=0; i<(1<<q); i++) fill(dp[i], dp[i] + n*n, inf);
    for(int i=0; i<q; i++) dp[1<<i][pt[i]] = 0;

    priority_queue<pair<ll,int>> pq;

    for(int mask = 1; mask < (1<<q); mask++){
        for(int sub = mask; sub; sub = (sub-1)&mask){
            if(sub==mask) continue;
            int rest = mask ^ sub;
            if(rest > sub) continue;
            for(int i=0; i<n*n; i++){
                dp[mask][i] = min(dp[mask][i], dp[sub][i] + dp[rest][i]);
            }
        }

        bool vis[n*n];
        memset(vis, 0, sizeof vis);

        for(int i=0; i<n*n; i++){
            if(dp[mask][i] == inf) continue;
            pq.push({-dp[mask][i], i});
        }

        while(!pq.empty()){
            ll cost = (-1)*pq.top().first, v = pq.top().second;
            pq.pop();
            if(vis[v]) continue;
            vis[v] = true;
            for(auto a : adj[v]){
                int u = a.first, c = a.second;
                if(dp[mask][u] > cost + c){
                    dp[mask][u] = cost + c;
                    pq.push({-dp[mask][u], u});
                }
            }
        }
    }

    ll ans = 0;
    for(int mask=1; mask < (1<<q); mask++){
        ll mn = inf;
        for(int i=0; i<n*n; i++){
            mn = min(mn, dp[mask][i]);
        }
        ans += mn;
    }

    cout << ans << "\n";