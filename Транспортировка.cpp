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

ll weight_bus = 3'000'000;
ll weight_cup = 100;

struct Edge {
    ll to, cost, max_weight;
};

bool dijkstra(ll curr_weight, vector<vector<Edge> > &graph) {
    ll start = 0, end = graph.size() - 1;
    vector<ll> dist(graph.size(),LLONG_MAX);
    dist[start] = 0;
    priority_queue<pair<ll,ll>, vector<pair<ll,ll> >, greater<> > pq;
    pq.push({dist[start], start});

    while (!pq.empty()) {
        ll path = pq.top().first;
        ll curr = pq.top().second;
        pq.pop();

        for (Edge &edge: graph[curr]) {
            if (edge.max_weight < curr_weight) {
                continue;
            }
            ll next = edge.to;
            ll cost = edge.cost;
            if (dist[next] > path + cost) {
                dist[next] = path + cost;
                pq.push({dist[next], next});
            }
        }
    }

    return dist[end] <= 1440;
}

void solution() {
    ll n, m;
    cin >> n >> m;

    vector<vector<Edge> > graph(n);

    for (ll index = 0; index < m; index++) {
        ll u, v, c, w;
        cin >> u >> v >> c >> w;
        u--, v--;
        graph[u].push_back({v, c, max((w - weight_bus) / weight_cup, 0LL)});
        graph[v].push_back({u, c, max((w - weight_bus) / weight_cup, 0LL)});
    }

    ll l = -1, r = 10000000 + 1;

    while (r - l > 1) {
        ll mid = (l + r) / 2;

        if (dijkstra(mid, graph)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << max(0LL, l) << endl;
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
