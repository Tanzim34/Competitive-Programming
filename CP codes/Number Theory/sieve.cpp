const int N = 1000;
vector<bool> is_prime(N+1,true);
vector<int> prime;

void sieve()
{
    is_prime[0] = is_prime[1] = false;
    for(int i=2; i*i<=N; i++)
    {
        if(is_prime[i])
        {
            for(int j=i*i; j<=N; j+=i) is_prime[j] = false;
        }
    }
    for(int i=2; i<=N; i++){
        if(is_prime[i]) prime.push_back(i);
    } 
}