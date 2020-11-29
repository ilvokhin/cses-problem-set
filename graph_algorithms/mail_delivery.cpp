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
        g[to].erase(x);

        find_cycle(g, to, cycle);
    }

    cycle.push_back(x + 1);
}

vector<int> find_cycle(graph& g)
{
    vector<int> cycle;

    find_cycle(g, 0, cycle);

    int n = g.size();
    for (int i = 0; i < n; ++i) {
        if (g[i].empty())
            continue;

        cycle.clear();
        break;
    }

    return cycle;
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

        g[a].insert(b);
        g[b].insert(a);
    }

    for (int x = 0; x < n; ++x) {
        if (g[x].size() % 2 == 0)
            continue;

        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    const vector<int> cycle = find_cycle(g);
    if (cycle.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    copy(cycle.begin(), cycle.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
