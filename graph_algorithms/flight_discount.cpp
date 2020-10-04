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

struct edge {
    int to;
    ll w;
};

using graph = vector<vector<edge>>;

vector<ll> dijkstra(const graph& g)
{
    int n = g.size();

    vector<ll> dist(n, INF);
    dist[0] = 0;
    set<pair<ll, int> > q;

    q.insert({0, 0});

    while (!q.empty()) {
        int x = q.begin()->second;
        q.erase(q.begin());

        for (const auto& e: g[x]) {
            if (dist[e.to] <= dist[x] + e.w)
                continue;

            if (dist[e.to] != INF)
                q.erase({dist[e.to], e.to});

            dist[e.to] = dist[x] + e.w;
            q.insert({dist[e.to], e.to});
        }
    }

    return dist;
}

vector<ll> half_dijkstra(const graph& g, const vector<ll>& dist)
{
    int n = g.size();

    vector<ll> hd(n, INF);
    hd[0] = 0;

    set<pair<ll, int> > q;
    q.insert({0, 0});

    while (!q.empty()) {
        int x = q.begin()->second;
        q.erase(q.begin());

        for (const auto& e: g[x]) {
            if (hd[e.to] <= hd[x] + e.w &&
                hd[e.to] <= dist[x] + e.w / 2)
                continue;

            if (hd[e.to] != INF)
                q.erase({hd[e.to], e.to});

            hd[e.to] = min({hd[x] + e.w, dist[x] + e.w / 2});
            q.insert({hd[e.to], e.to});
        }
    }

    return hd;
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        ll c;

        cin >> a >> b >> c;
        --a, --b;

        g[a].push_back({b, c});
    }

    const vector<ll> dist = dijkstra(g);
    const vector<ll> hd = half_dijkstra(g, dist);

    cout << hd[n - 1] << endl;

    return 0;
}
