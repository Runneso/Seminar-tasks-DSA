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
#define print(x) for(auto element:x) cout << element << " ";
#define endl "\n"

// freopen("file.txt","r",stdin);
// getline(cin,string);
// num % mod = (num % mod + mod) % mod
// rand() % (end - start + 1) + start;

unordered_set<ll> find_cutpoints(const vector<vector<ll> > &graph) {
    vector<bool> visited(graph.size(), false);
    vector<ll> tin(graph.size());
    vector<ll> up(graph.size());
    unordered_set<ll> ans;
    ll time = 0;

    function<void(ll, ll)> dfs = [&](ll v, ll p) {
        visited[v] = true;
        ll child_cnt = 0;
        tin[v] = up[v] = ++time;

        for (ll u: graph[v]) {
            if (u == p) {
                continue;
            }
            if (!visited[u]) {
                ++child_cnt;
                dfs(u, v);
                up[v] = min(up[u], up[v]);

                if (up[u] >= tin[v] && p != -1) {
                    ans.insert(v);
                }
            } else {
                up[v] = min(tin[u], up[v]);
            }
        }

        if (p == -1 && child_cnt > 1) {
            ans.insert(v);
        }
    };

    for (ll v = 0; v < graph.size(); ++v) {
        if (!visited[v])
            dfs(v, -1);
    }

    return ans;
}

void solution() {
    ll n, m;
    cin >> n >> m;

    vector<vector<ll> > graph(n);
    ll a, b;
    while (m--) {
        cin >> a >> b;
        --a, --b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    ll s, e;
    cin >> s >> e;
    --s, --e;

    unordered_set<ll> cutpoints = find_cutpoints(graph);
    vector<ll> dist(n,LLONG_MAX);
    dist[s] = 0;

    deque<ll> q;
    vector<ll> parents(n, 0);
    parents[s] = -1;
    q.push_back(s);

    while (!q.empty()) {
        ll curr = q.front();
        q.pop_front();

        for (ll next: graph[curr]) {
            ll weight = (cutpoints.count(next) ? 1 : 0);

            if (dist[next] > dist[curr] + weight) {
                dist[next] = dist[curr] + weight;
                parents[next] = curr;

                if (weight == 0) {
                    q.push_front(next);
                } else {
                    q.push_back(next);
                }
            }
        }
    }

    vector<ll> path;

    ll curr = e;
    while (curr != -1) {
        if (cutpoints.count(curr) && curr != s && curr != e) {
            path.push_back(curr + 1);
        }
        curr = parents[curr];
    }
    cout << path.size() << endl;
    sort(all(path));
    print(path);
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
