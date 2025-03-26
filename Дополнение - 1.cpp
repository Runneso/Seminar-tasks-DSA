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

struct Edge {
    ll u, v, cost;

    bool operator==(const Edge &rhs) const {
        return (this->u == rhs.u && this->v == rhs.v && this->cost == rhs.cost);
    }
};

struct DSU {
    ll n;
    vector<ll> parents;
    vector<ll> ranks;

    DSU(ll n) {
        this->n = n;
        parents.resize(n);
        ranks.resize(n, 0);
        for (ll index = 0; index < n; index++) {
            parents[index] = index;
        }
    }

    ll find_set(ll x) {
        if (x == parents[x]) {
            return x;
        }
        return parents[x] = find_set(parents[x]);
    }

    void unite(ll xx,ll yy) {
        ll x = find_set(xx);
        ll y = find_set(yy);
        if (x == y) {
            return;
        }
        if (ranks[x] < ranks[y]) {
            swap(x, y);
        }
        parents[y] = x;
        if (ranks[x] == ranks[y]) {
            ranks[x]++;
        }
    }
};




void solution() {
    ll n;
    cin >> n;
    vector<Edge> edges;
    DSU snm(n);

    for(ll index_i=0; index_i<n; index_i++) {
        for (ll index_j=0;index_j<n;index_j++) {
            ll cost;
            cin >> cost;
            edges.push_back({index_i,index_j,cost});
        }
    }

    for(ll index_i=0; index_i<n; index_i++) {
        for (ll index_j=0;index_j<n;index_j++) {
            ll have;
            cin >> have;
            if(have == 1) {
                snm.unite(index_i,index_j);
            }
        }
    }
    sort(all(edges), [](const Edge &lhs, const Edge &rhs) {
        return lhs.cost < rhs.cost;
    });
    ll cost = 0;
    for (Edge &edge : edges) {
        if (snm.find_set(edge.u) != snm.find_set(edge.v)) {
            cost += edge.cost;
            snm.unite(edge.u, edge.v);
        }
    }
    cout << cost << endl;
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