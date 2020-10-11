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

bool dfs(const graph& g, int x, vector<int>& used, vector<int>& order)
{
    used[x] = 1;

    for (int to: g[x]) {
        if (used[to] == 1)
            return true;

        if (used[to] == 2)
            continue;

        if (dfs(g, to, used, order))
            return true;
    }

    used[x] = 2;
    order.push_back(x + 1);
    return false;
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
    vector<int> order;

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            if(dfs(g, i, used, order)) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    copy(order.rbegin(), order.rend(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
