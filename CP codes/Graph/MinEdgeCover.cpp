struct EdgeCover {

    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    EdgeCover(int V) : V(V), adj(V) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        // adj[v].push_back(u);
    }

    // Edmonds' Blossom Algorithm for Maximum Matching
    vector<int> maximumMatching() {
        vector<int> match(V, -1), parent(V, -1), base(V);
        vector<bool> used(V, false), blossom(V, false);

        auto lca = [&](int a, int b) {
            vector<bool> visited(V, false);
            while (true) {
                a = base[a];
                visited[a] = true;
                if (match[a] == -1) break;
                a = parent[match[a]];
            }
            while (true) {
                b = base[b];
                if (visited[b]) return b;
                b = parent[match[b]];
            }
        };

        auto markBlossom = [&](int u, int ancestor, queue<int> &q) {
            while (base[u] != ancestor) {
                blossom[base[u]] = blossom[base[match[u]]] = true;
                parent[u] = match[u];
                q.push(match[u]);
                u = parent[match[u]];
            }
        };

        auto findAugmentingPath = [&](int root) {
            fill(parent.begin(), parent.end(), -1);
            fill(used.begin(), used.end(), false);
            fill(blossom.begin(), blossom.end(), false);
            for (int i = 0; i < V; ++i) base[i] = i;

            queue<int> q;
            q.push(root);
            used[root] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (base[u] == base[v] || match[u] == v) continue;

                    if (v == root || (match[v] != -1 && parent[match[v]] != -1)) {
                        int ancestor = lca(u, v);
                        markBlossom(u, ancestor, q);
                        markBlossom(v, ancestor, q);
                    } else if (parent[v] == -1) {
                        parent[v] = u;
                        if (match[v] == -1) return v;
                        q.push(match[v]);
                        used[match[v]] = true;
                    }
                }
            }
            return -1ll;
        };

        auto augmentPath = [&](int u) {
            while (u != -1) {
                int pv = parent[u], ppv = match[pv];
                match[u] = pv;
                match[pv] = u;
                u = ppv;
            }
        };

        for (int i = 0; i < V; ++i) {
            if (match[i] == -1) {
                int v = findAugmentingPath(i);
                if (v != -1) augmentPath(v);
            }
        }

        return match;
    }

    // Minimum Edge Cover
    vector<pair<int, int>> minEdgeCover() {
        vector<int> match = maximumMatching();
        vector<bool> covered(V, false);
        vector<pair<int, int>> edgeCover;

        // Add edges from the matching
        for (int u = 0; u < V; ++u) {
            if (match[u] != -1 && !covered[u]) {
                edgeCover.emplace_back(u, match[u]);
                covered[u] = true;
                covered[match[u]] = true;
            }
        }

        // Add edges to cover uncovered vertices
        // Assuming a edge cover exists
        // If does not exist , we can add the uncovered vertices as a single self edge
        for (int u = 0; u < V; ++u) {
            if (!covered[u]) {
                for (int v : adj[u]) {
                    if (!covered[v]) {
                        edgeCover.emplace_back(u, v);
                        covered[u] = true;
                        covered[v] = true;
                        break;
                    }
                }
            }
        }


        return edgeCover;
    }
};