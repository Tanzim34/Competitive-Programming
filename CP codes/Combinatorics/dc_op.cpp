int ara[N], dp[N][K], cst = 0, L = 0, R = 0;
 
int cnt[N];
 
void addBack(int id){
    int val = ara[id];
    cst += cnt[val];
    cnt[val]++;
}
 
void addFront(int id){
    int val = ara[id];
    cst += cnt[val];
    cnt[val]++;
}
 
void removeFront(int id){
    int val = ara[id];
    if(!cnt[val]) return;
    cst -= (cnt[val]-1);
    cnt[val]--;
}
 
void removeBack(int id){
    int val = ara[id];
    if(!cnt[val]) return;
    cst -= (cnt[val]-1);
    cnt[val]--;
}
 
int find_cost(int l, int r){
     if(l < L){
        while(l<L) L--, addBack(L);
        while(l>L) removeBack(L), L++;
        while(r<R) removeFront(R), R--;
        while(r>R) R++, addFront(R);
    }
    else{
        while(r<R) removeFront(R), R--;
        while(r>R) R++, addFront(R);
        while(l<L) L--, addBack(L);
        while(l>L) removeBack(L), L++;
    }
    return cst; 
}
 
 
void compute(int k, int l, int r, int optl, int optr){
    if(r < l) return ;
    int mid = (l+r)/2;
    int cost = inf, optnow = -1;
    for(int i=optl; i<=optr && i < mid; i++){
        int ret = find_cost(i+1, mid);
        if(ret + dp[i][k-1] < cost){
            cost = ret + dp[i][k-1];
            optnow = i;
        }
    }
    dp[mid][k] = cost;
    compute(k, l, mid-1, optl, optnow);
    compute(k, mid+1, r, optnow, optr);
}