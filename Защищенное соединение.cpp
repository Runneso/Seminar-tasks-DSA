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


void solution() {
    ll n,m;
    cin>>n>>m;
    ll a = n,b = n+1;
    vector<vector<pair<ll,ll>>> graph(n+2);
    vector<ll> color(n);
    for(ll index=0;index<n;index++) {
        cin>>color[index];
    }
    for (ll index=0;index<m;index++) {
        ll u,v,c;
        cin>>u>>v>>c;
        u--,v--;
        graph[u].push_back({v,c});
        graph[v].push_back({u,c});

    }

    for (ll index = 0; index < n; index++) {
        if (color[index] == 1) {
            graph[a].push_back({index, 0});
            graph[index].push_back({a, 0});
        }
        if (color[index] == 2) {
            graph[b].push_back({index, 0});
            graph[index].push_back({b, 0});
        }
    }

    vector<ll> dist(n+2,LLONG_MAX);
    vector<ll> parents(n+2,LLONG_MAX);
    dist[a]=0;
    parents[a]=-1;

    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> pq;
    pq.push({dist[a],a});
    while(!pq.empty()) {
        ll path = pq.top().first;
        ll curr = pq.top().second;
        pq.pop();

        for (auto edge : graph[curr]) {
            ll cost = edge.second;
            ll next = edge.first;

            if (dist[next] > path + cost) {
                dist[next] = path + cost;
                parents[next] = curr;
                pq.push({dist[next],next});
            }
        }
    }

    if (dist[b] == LLONG_MAX) {
        cout<<-1;
        return;
    }

    ll end = b;
    vector<ll> path;
    while(end != -1) {
        path.push_back(end);
        end = parents[end];
    }
    reverse(all(path));
    cout<< path[1]+1 << " " << path[path.size()-2]+1 << " " << dist[b];
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
