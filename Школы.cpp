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

    bool operator==(const Edge& rhs) const {
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


ll findMST(ll n, vector<Edge> edges) {
    ll curr = 0;
    ll count = 0;
    DSU snm(n);

    for (Edge &edge: edges) {
        if (snm.find_set(edge.u) != snm.find_set(edge.v)) {
            curr += edge.cost;
            snm.unite(edge.u, edge.v);
            count++;
        }
    }
    if (count!= n-1 ) {
        return LLONG_MAX;
    }
    return curr;


}


void solution() {
    ll n, m;
    cin >> n >> m;
    DSU snm(n);
    vector<Edge> edges;
    for (ll index = 0; index < m; index++) {
        ll u, v, cost;
        cin >> u >> v >> cost;
        u--, v--;
        edges.push_back({u, v, cost});
    }
    sort(all(edges), [](const Edge &e1, const Edge &e2) {
        return e1.cost < e2.cost;
    });

    vector<Edge> MST;
    ll cost = 0;
    for (Edge &edge: edges) {
        if (snm.find_set(edge.u) != snm.find_set(edge.v)) {
            cost += edge.cost;
            snm.unite(edge.u, edge.v);
            MST.push_back(edge);
        }
    }
    ll cost2 = LLONG_MAX;

    for (Edge &edge: MST) {
        Edge curr = edge;
        edges.erase(find(edges.begin(), edges.end(), curr));
        cost2=  min(cost2,findMST(n, edges));
        edges.push_back(curr);
        sort(all(edges), [](const Edge &e1, const Edge &e2) {
       return e1.cost < e2.cost;
   });
    }

    cout<<cost << " "<<cost2<<endl;
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