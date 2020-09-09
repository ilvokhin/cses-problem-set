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

vector<int> restore_path(int end, int begin, const vector<int>& parent)
{
    int cur = end;
    vector<int> path = { end };

    while (cur != begin) {
        int prev = parent[cur];
        path.push_back(prev);
        cur = prev;
    }

    for (int& x: path)
        ++x;

    reverse(path.begin(), path.end());
    return path;
}

vector<int> bfs(const graph& g, int begin, int end)
{
    int n = g.size();
    vector<bool> used(n);
    vector<int> parent(n);
    queue<int> q;

    parent[begin] = -1;
    used[begin] = true;
    q.push(begin);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == end)
            return restore_path(end, begin, parent);

        for (int x: g[cur]) {
            if (used[x])
                continue;

            parent[x] = cur;
            used[x] = true;
            q.push(x);
        }
    }

    return {};
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int a = 0, b = 0;
        cin >> a >> b;
        --a, --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }   

    vector<int> path = bfs(g, 0, n - 1);

    if (path.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    cout << path.size() << endl;
    copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
