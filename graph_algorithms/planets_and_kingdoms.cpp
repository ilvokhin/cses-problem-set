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

void find_order(const graph& g, int x, vector<bool>& used, vector<int>& order)
{
    used[x] = true;

    for (int to: g[x]) {
        if (used[to])
            continue;

        find_order(g, to, used, order);
    }

    order.push_back(x);
}

void find_scc(const graph& g, int x, int scc_num, vector<int>& scc,
              vector<bool>& used)
{
    used[x] = true;
    scc[x] = scc_num;

    for (int to: g[x]) {
        if (used[to])
            continue;

        find_scc(g, to, scc_num, scc, used);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);
    graph rg(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        rg[b].push_back(a);
    }

    vector<bool> used(n);
    vector<int> order;

    for (int i = 0; i < n; ++i) {
        if (used[i])
            continue;

        find_order(g, i, used, order);
    }
    reverse(order.begin(), order.end());

    fill(used.begin(), used.end(), false);
    int scc_num = 1;
    vector<int> scc(n, -1);

    for (int i: order) {
        if (used[i])
            continue;

        find_scc(rg, i, scc_num, scc, used);
        ++scc_num;
    }

    cout << scc_num - 1 << endl;
    copy(scc.begin(), scc.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
