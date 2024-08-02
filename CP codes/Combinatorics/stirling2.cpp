ll stirling(ll n, ll k)
{
	ll val = 0;
   	for(int j=0; j<=k; j++)
   	{
   		ll a = nCr(k,j);
   		a = (a*binpow(j,n,mod))%mod;
   		if(j%2==k%2) val = (val+a)%mod;
   		else val = (val-a+mod)%mod;
 
   		// cout << val << " ";
   	}
   	val = (val*inv[k])%mod;
   	return val;
}