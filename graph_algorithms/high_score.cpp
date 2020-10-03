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
    int from;
    int to;
    ll w;
};

bool dfs(const vector<vector<int>>& g, int x, const vector<bool>& updated,
         vector<bool>& used)
{
    if (updated[x])
        return true;

    used[x] = true;

    for (int to: g[x]) {
        if (used[to])
            continue;

        if (dfs(g, to, updated, used))
            return true;
    }

    return false;
}

bool is_reacheble(const vector<edge>& edges, const vector<bool>& updated, int n)
{
    vector<vector<int>> g(n);

    for(const auto& e: edges)
        g[e.to].push_back(e.from);

    vector<bool> used(n);

    return dfs(g, n - 1, updated, used);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<edge> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].w;
        --edges[i].from;
        --edges[i].to;
        edges[i].w = -edges[i].w;
    }

    vector<ll> dist(n, INF);
    dist[0] = 0;

    for (int k = 0; k < n - 1; ++k) {
        for (int i = 0; i < m; ++i) {
            if (dist[edges[i].from] == INF)
                continue;

            dist[edges[i].to] = min(dist[edges[i].to],
                                    dist[edges[i].from] + edges[i].w);
        }
    }

    vector<bool> updated(n);

    for (int i = 0; i < m; ++i) {
        if (dist[edges[i].from] == INF)
                continue;

        if (dist[edges[i].to] > dist[edges[i].from] + edges[i].w)
            updated[edges[i].to] = true;
    }

    if (is_reacheble(edges, updated, n)) {
        cout << -1 << endl;
        return 0;
    }

    cout << -dist[n - 1] << endl;
    
    return 0;
}
