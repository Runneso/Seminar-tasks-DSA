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


void solution() {
    ll n;
    cin >> n;

    vector<vector<ll> > graph(n);
    vector<ll> inDegree(n, 0);

    for (ll index = 0; index < n; index++) {
        ll neighbours;
        cin >> neighbours;

        while (neighbours--) {
            ll curr;
            cin >> curr;
            curr--;
            graph[index].push_back(curr);
            inDegree[curr]++;
        }
    }

    priority_queue<ll> pq;

    for (ll index = 0; index < n; index++) {
        if (inDegree[index] == 0) {
            pq.push(index);
        }
    }
    vector<ll> order;
    while (!pq.empty()) {
        ll curr = pq.top();
        pq.pop();
        order.push_back(curr);

        for (ll next: graph[curr]) {
            inDegree[next]--;
            if (inDegree[next] == 0) {
                pq.push(next);
            }
        }
    }
    reverse(all(order));
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
