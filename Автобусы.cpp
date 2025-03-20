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
    ll to,start_time,end_time;
};

void solution() {
    ll n;
    cin>>n;
    ll start,end;
    cin>>start>>end;
    start--,end--;
    ll m;
    cin>>m;

    vector<vector<Edge>> graph(n);

    for(ll index=0;index<m;index++) {
        ll from,to,start_time,end_time;
        cin>>from>>start_time>>to>>end_time;
        from--,to--;
        graph[from].push_back({to,start_time,end_time});
    }

    vector<ll> dist(n,LLONG_MAX);
    dist[start]=0;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>> pq;
    pq.push({dist[start],start});
    while(!pq.empty()) {
        ll path = pq.top().first;
        ll curr = pq.top().second;
        pq.pop();

        for (Edge &edge : graph[curr]) {
            if (path > edge.start_time) {
                continue;
            }
            if (dist[edge.to] > edge.end_time) {
                dist[edge.to] = edge.end_time;
                pq.push({dist[edge.to],edge.to});
            }

        }

    }

    if (dist[end] == LLONG_MAX) {
        cout<<-1;
    }else {
        cout<<dist[end];
    }
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

