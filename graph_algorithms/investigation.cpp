#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <utility>
#include <string>
#include <vector>
#include <limits>
#include <queue>
#include <cmath>
#include <map>
#include <set>

using namespace std;

using ll = long long;
const ll INF = numeric_limits<ll>::max();
const ll MOD = 1e9 + 7;

struct edge {
    int to;
    ll w;
};

using graph = vector<vector<edge>>;

void solve(const graph& g)
{
    int n = g.size();

    vector<ll> dist(n, INF);
    vector<ll> cnt(n, 0);
    vector<ll> mn(n, INF);
    vector<ll> mx(n, 0);

    set<pair<ll, int> > pq;
    dist[0] = 0;
    cnt[0] = 1;
    mn[0] = mx[0] = 0;
    pq.insert({0, 0});

    while (!pq.empty()) {
        auto p = *pq.begin();
        pq.erase(pq.begin());

        int cur = p.second;

        for (const edge& e: g[cur]) {
            if (dist[e.to] < dist[cur] + e.w) {
                continue;
            } else if (dist[e.to] == dist[cur] + e.w) {
                cnt[e.to] = (cnt[e.to] + cnt[cur]) % MOD;
                mn[e.to] = min(mn[e.to], mn[cur] + 1);
                mx[e.to] = max(mx[e.to], mx[cur] + 1);

                continue;
            }

            if (dist[e.to] != INF)
                pq.erase({dist[e.to], e.to});

            dist[e.to] = dist[cur] + e.w;
            cnt[e.to] = cnt[cur];
            mn[e.to] = mn[cur] + 1;
            mx[e.to] = mx[cur] + 1;
            pq.insert({dist[e.to], e.to});
        }
    }

    cout << dist[n - 1] << " "
         << cnt[n - 1] << " "
         << mn[n - 1] << " "
         << mx[n - 1] << endl;
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;

        g[a].push_back({b, c});
    }

    solve(g);

    return 0;
}
