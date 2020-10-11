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

bool find_cycle(const graph& g, int x, vector<int>& used, vector<int>& parent,
                int& start, int& end)
{
    used[x] = 1;

    for (int to : g[x]) {
        if (used[to] == 1) {
            end = x;
            start = to;
            return true;
        }

        if (!used[to]) {
            parent[to] = x;
            if (find_cycle(g, to, used, parent, start, end))
                return true;
        }
    }

    used[x] = 2;
    return false;
}

vector<int> restore_path(int end, int begin, const vector<int>& parent)
{
    vector<int> path = { end + 1 };
    int cur = end;

    while (cur != begin) {
        int prev = parent[cur];
        path.push_back(prev + 1);
        cur = prev;
    }

    reverse(path.begin(), path.end());
    path.push_back(path[0]);

    return path;
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

    vector<int> used(n);
    vector<int> parent(n, -1);

    for (int i = 0; i < n; ++i) {
        if (used[i])
            continue;

        int start = -1, end = -1;
        if (!find_cycle(g, i, used, parent, start, end))
            continue;

        vector<int> cycle = restore_path(end, start, parent);

        cout << cycle.size() << endl;
        copy(cycle.begin(), cycle.end(), ostream_iterator<int>(cout, " "));
        cout << endl;

        return 0;
    }

    cout << "IMPOSSIBLE" << endl;

    return 0;
}
