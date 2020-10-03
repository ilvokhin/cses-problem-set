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
    int w;
};

using graph = vector<vector<edge>>;

vector<ll> dijkstra(const graph& g)
{
    int n = g.size();

    set<pair<ll, int> > q;
    vector<ll> dist(n, INF);

    dist[0] = 0;
    q.insert({0, 0});

    while (!q.empty()) {
        const pair<ll, int> p = *q.begin();
        q.erase(q.begin());

        int x = p.second;
        ll cur_dist = p.first;

        for (const auto& e: g[x]) {
            if (dist[e.to] == INF) {
                dist[e.to] = cur_dist + e.w;
                q.insert({dist[e.to], e.to});
                continue;
            }

            if (dist[e.to] < cur_dist + e.w)
                continue;

            q.erase({dist[e.to], e.to});
            dist[e.to] = cur_dist + e.w;
            q.insert({dist[e.to], e.to});
        }
    }

    return dist;
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

    vector<ll> dist = dijkstra(g);

    copy(dist.begin(), dist.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}
