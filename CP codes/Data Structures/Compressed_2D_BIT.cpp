#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

// #define int long long
// #define ld long double

// typedef long long ll;

#pragma GCC optimize("O3")
#pragma GCC target("avx2")

const int N = 100001;
const int inf = 1e9; 

// This only works for binary data in the grid
// Complexity - T - O(log^2n) per query, S - O(Qlogn)

typedef tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update> OST;

OST bit[N];

void insert(int x, int y)
{
  for(int i = x; i < N; i += i & -i)
    bit[i].insert(make_pair(y, x));
}

void remove(int x, int y)
{
  for(int i = x; i < N; i += i & -i)
    bit[i].erase(make_pair(y, x));
}

int sum(int x, int y)
{
  int ans = 0;
  for(int i = x; i > 0; i -= i & -i)
    ans += bit[i].order_of_key(make_pair(y+1, 0));
  return ans;
}

int query(int r1, int c1, int r2, int c2) {
    return sum(r2, c2) - sum(r2, c1 - 1) - sum(r1 - 1, c2) +
           sum(r1 - 1, c1 - 1);
  }