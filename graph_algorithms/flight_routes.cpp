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

struct edge {
    int to;
    ll w;
};

using graph = vector<vector<edge>>;

vector<ll> find_shortest_k(const graph& g, int start, int end, int k)
{
    int n = g.size();

    priority_queue<pair<ll, int>,
                   vector<pair<ll, int>>,
                   greater<pair<ll, int>>> pq;

    vector<ll> dist;
    vector<int> cnt(n, 0);

    pq.push({0, start});

    while (!pq.empty() && cnt[end] < k) {
        auto p = pq.top();
        pq.pop();

        ll cur_dist = p.first;
        int cur = p.second;

        if (cur == end)
            dist.push_back(cur_dist);

        if (cnt[cur] >= k)
            continue;

        ++cnt[cur];

        for (const edge& e: g[cur])
            pq.push({cur_dist + e.w, e.to});
    }

    return dist;
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int from;
        edge e;

        cin >> from >> e.to >> e.w;
        --from, --e.to;

        g[from].push_back(e);
    }

    vector<ll> dist = find_shortest_k(g, 0, n - 1, k);

    copy(dist.begin(), dist.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}
