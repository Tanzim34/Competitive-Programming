const int mod1 = 127657753, mod2 = 987654319;
const int p1 = 137, p2 = 277;
pair<int,int> pw[N], inv[N];

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void precalcu(){
    pw[0] = {1, 1};
    for(int i=1; i<N; i++){
        pw[i].first = (1ll*pw[i-1].first * p1) % mod1;
        pw[i].second = (1ll*pw[i-1].second * p2) % mod2;
    }
    inv[N-1].first = binpow(pw[N-1].first, mod1-2, mod1);
    inv[N-1].second = binpow(pw[N-1].second, mod2-2, mod2);

    for(int i=N-2; i>=0; i--){
        inv[i].first = (1ll*inv[i+1].first * p1) % mod1;
        inv[i].second = (1ll*inv[i+1].second * p2) % mod2;
    }
}

struct Hashing
{
    int n;
    string s;
    vector<pair<int,int>> hs; 

    Hashing() {}
    Hashing(string _s){
        n = _s.size();
        s = _s;
        hs.emplace_back(0, 0);
        
        for(int i=0; i<n; i++){
            pair<int,int> p;
            p.first = (hs[i].first + (1ll*pw[i].first * s[i]) % mod1) % mod1;
            p.second = (hs[i].second + (1ll*pw[i].second * s[i]) % mod2) % mod2;
            hs.push_back(p);
        }
    }

    pair<int,int> get_hash(int l, int r){  // 1- indexed
        assert(1 <= l && l <= r && r <= n);
        pair<int,int> ans;

        ans.first = ((hs[r].first - hs[l-1].first + mod1) * 1ll * inv[l-1].first) % mod1;
        ans.second = ((hs[r].second - hs[l-1].second + mod2) * 1ll * inv[l-1].second) % mod2;

        return ans;
    }

     pair<int, int> get_hash() {
        return get_hash(1, n);
    }
};