#include <unordered_set>
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
using graph = vector<unordered_set<int>>;

void find_cycle(graph& g, int x, vector<int>& cycle)
{
    while (!g[x].empty()) {
        auto it = g[x].begin();
        int to = *it;

        g[x].erase(it);
        find_cycle(g, to, cycle);
    }

    cycle.push_back(x);
}

vector<int> find_cycle(graph& g)
{
    vector<int> cycle;
    find_cycle(g, 0, cycle);

    for (size_t x = 0; x < g.size(); ++x) {
        if (g[x].empty())
            continue;

        cycle.clear();
        break;
    }

    return cycle;
}

vector<int> remove_edge(int from, int to, vector<int>& cycle)
{
    int n = cycle.size();

    for (int i = 0; i < n - 1; ++i) {
        if (cycle[i] != from || cycle[i + 1] != to)
            continue;

        vector<int> next;
        next.reserve(n - 1);

        for (int j = i + 1; j < n; ++j)
            next.push_back(cycle[j]);

        // exclude first vertex
        for (int j = 1; j < i + 1; ++j)
            next.push_back(cycle[j]);

        return next;
    }

    assert(false);
    return cycle;
}

void impossible()
{
    cout << "IMPOSSIBLE" << endl;
    exit(0);
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);
    vector<int> in(n);
    vector<int> out(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        g[a].insert(b);
        ++out[a];
        ++in[b];
    }

    int x = -1, y = -1;
    for (int i = 0; i < n; ++i) {
        if (in[i] + 1 == out[i]) {
            if (x != -1)
                impossible();
            x = i;
        }

        if (in[i] == out[i] + 1) {
            if (y != -1)
                impossible();
            y = i;
        }
    }

    if (y != n - 1 && x != 0)
        impossible();

    if (x != -1 && y != -1)
        g[y].insert(x);

    vector<int> cycle = find_cycle(g);
    if (cycle.empty())
        impossible();

    std::reverse(cycle.begin(), cycle.end());
    if (x != -1 && y != -1)
        cycle = remove_edge(y, x, cycle);

    if (cycle[0] != 0 || cycle.back() != n - 1)
        impossible();

    for (int x: cycle)
        cout << x + 1 << " ";
    cout << endl;

    return 0;
}
