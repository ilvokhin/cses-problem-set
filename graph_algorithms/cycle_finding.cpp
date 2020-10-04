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

vector<int> restore_cycle(int end, const vector<int>& parent)
{
    vector<int> cycle;

    int cur = end;

    do {
        assert(cur != -1);
        cycle.push_back(cur + 1);
        cur = parent[cur];
    } while(cur != end);

    cycle.push_back(cur + 1);

    reverse(cycle.begin(), cycle.end());

    return cycle;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<edge> edges(m);

    for (int i = 0; i < m; ++i) {
        cin >> edges[i].from >> edges[i].to >> edges[i].w;
        --edges[i].to;
        --edges[i].from;
    }

    vector<ll> dist(n, 0);

    vector<int> parent(n, -1);

    int x = -1;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (const edge& e: edges) {
            if (dist[e.from] == INF)
                continue;

            if (dist[e.to] > dist[e.from] + e.w) {
                dist[e.to] = dist[e.from] + e.w;
                parent[e.to] = e.from;
                x = e.to;
            }
        }
    }

    if(x != -1) {
        for (int i = 0; i < n; ++i)
            x = parent[x];

        const vector<int> cycle = restore_cycle(x, parent);

        cout << "YES" << endl;
        copy(cycle.begin(), cycle.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

        return 0;
    }

    cout << "NO" << endl;

    return 0;
}
