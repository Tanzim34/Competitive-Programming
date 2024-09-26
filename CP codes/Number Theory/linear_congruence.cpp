// Solve ax==b (mod m) - O(log n)
int linear_congruence(int a, int b, int m){
    int d = __gcd(a,m);
    if(b%d!=0) return -1;
    a/=d, b/=d, m/=d;
    int x,y;
    gcd(a,m,x,y);
    x = (x*b)%m;
    while(x<0) x+=m;
    return x;
}