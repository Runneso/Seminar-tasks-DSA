#include <bits/stdc++.h>

using namespace std;

#pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2,avx512,fma")

#define ll int
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
    ll id,u, v, cost;
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


void knapspack01(
    vector<Edge> edges,
    ll T_total,
    ll Qexp,
    ll Qcheap,
    ll cheapPrice,
    ll expensivePrice,
    ll cheapCat,
    ll expensiveCat
    ) {
    ll lowerBound = max(0, T_total - Qexp);
    ll upperBound = Qcheap;

    ll n = edges.size();
    vector<unordered_map<ll, pair<ll,ll>>> dp(n + 1);
    dp[0][0] = {-1, -1};

    for (ll index = 0; index < n; index++) {
        ll w = edges[index].cost;
        for (auto &entry : dp[index]) {
            ll curSum = entry.first;
            if(dp[index+1].find(curSum) == dp[index+1].end())
                dp[index+1][curSum] = {curSum, 0};
            if(curSum + w <= upperBound) {
                if(dp[index+1].find(curSum + w) == dp[index+1].end())
                    dp[index+1][curSum + w] = {curSum, 1};
            }
        }
    }



    ll bestS = -1;
    for(auto &entry : dp[n]) {
        ll s = entry.first;
        if(s >= lowerBound && s <= upperBound) {
            bestS = max(bestS, s);
        }
    }
    if(bestS == -1) {
        cout << "Impossible";
        return;
    }

    vector<ll> decision(n, 0); // 1 - дешёвый, 0 - дорогой
    ll cur = bestS;
    for (ll index = n; index > 0; index--) {
        auto prev = dp[index][cur];
        decision[index-1] = prev.second;
        cur = prev.first;
    }

    ll totalCost = bestS * cheapPrice + (T_total - bestS) * expensivePrice;
    cout << totalCost << endl;
    for (ll index = 0; index < n; index++) {
        ll cat = decision[index] ? cheapCat : expensiveCat;
        cout << edges[index].id << " " << cat << endl;
    }
}


void solution() {
    ll n, m;
    cin >> n >> m;

    vector<Edge> edges;
    DSU snm(n);
    for (ll index = 0; index < m; index++) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--, v--;
        edges.push_back({index+1,u, v, c});
    }

    sort(all(edges), [ ](const Edge &e1, const Edge &e2) {
        return e1.cost < e2.cost;
    });


    vector<Edge> costs;

    for (Edge &edge: edges) {
        if (snm.find_set(edge.u) != snm.find_set(edge.v)) {
            costs.push_back(edge);
            snm.unite(edge.u, edge.v);
        }
    }

    if(costs.size() != n-1) {
        cout << "Impossible";
        return;
    }

    ll p5, q5, p6, q6;
    cin >> p5 >> q5 >> p6 >> q6;
    ll cheapCat, expensiveCat;
    ll cheapPrice, expensivePrice, Qcheap, Qexp;
    if(p5 <= p6) {
        cheapCat = 5; expensiveCat = 6;
        cheapPrice = p5; expensivePrice = p6;
        Qcheap = q5; Qexp = q6;
    } else {
        cheapCat = 6; expensiveCat = 5;
        cheapPrice = p6; expensivePrice = p5;
        Qcheap = q6; Qexp = q5;
    }


    ll T_total = 0;
    for(auto &e : costs)
        T_total += e.cost;

    if(T_total > Qcheap + Qexp) {
        cout << "Impossible";
        return;
    }
    knapspack01(costs,T_total,Qexp,Qcheap,cheapPrice,expensivePrice,cheapCat,expensiveCat);

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