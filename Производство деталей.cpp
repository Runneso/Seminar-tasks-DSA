#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,avx512,fma")

#define ll long long int
#define ld long double

#define PI acos(-1)
#define inf LONG_LONG_MAX
#define MOD (1'000'000'000+7)
#define MOD2 (1'000'000'000+9)
#define EPS 1e-9
#define all(x) x.begin(),x.end()
#define print(x) for(auto element:x) cout << element+1 << " ";
#define endl "\n"

// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;
ll timer = 0;

void dfs(ll node,vector<bool> &visited,vector<ll> &order,vector<vector<ll>> &graph, vector<ll> &array) {
    visited[node] = true;
    timer+=array[node];

    for (ll next : graph[node]) {
        if (!visited[next]) {
            dfs(next,visited,order,graph,array);
        }
    }
    order.push_back(node);
}

void solution() {
    ll n;
    cin>>n;

    vector<ll> array(n);
    for (ll index=0;index<n;index++) {
        cin>>array[index];
    }

    vector<vector<ll>> graph(n);

    for (ll index=0;index<n;index++) {
        ll neighbors;
        cin>>neighbors;

        while (neighbors--) {
            ll curr;
            cin>>curr;
            curr--;
            graph[index].push_back(curr);
        }
    }

    vector<bool> visited(n,false);
    vector<ll> order;

    dfs(0,visited,order,graph,array);
    cout << timer << ' ' << order.size() << endl;
    print(order);
}

int main() {
    srand(time(nullptr));
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    ll t = 1;
    // cin>>t;
    while (t--) {
        solution();
    }
}
