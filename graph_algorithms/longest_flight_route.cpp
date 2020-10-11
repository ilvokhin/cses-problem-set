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
using graph = vector<vector<int>>;

bool dfs(const graph& g, int x, vector<bool>& used, vector<int>& dist,
         vector<int>& next)
{
    used[x] = true;

    int n = g.size();
    if (x == n - 1) {
        used[x] = true;
        dist[x] = 0;
        return true;
    }

    int mx = -1;
    int nxt = -1;

    for (int to: g[x]) {
            if (!used[to])
                dfs(g, to, used, dist, next);

        if (dist[to] > mx) {
            mx = dist[to];
            nxt = to;
        }
    }

    if (mx != -1) {
        dist[x] = mx + 1;
        next[x] = nxt;
    }

    return dist[x] != -1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        g[a].push_back(b);
    }

    vector<bool> used(n);
    vector<int> dist(n, -1);
    vector<int> next(n, -1);

    if (!dfs(g, 0, used, dist, next)) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<int> path;
    int cur = 0;

    while (cur != -1) {
        path.push_back(cur + 1);
        cur = next[cur];
    }

    cout << path.size() << endl;
    copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
