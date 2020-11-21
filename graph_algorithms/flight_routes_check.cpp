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

void find_scc(const graph& g, int x, int comp, vector<bool>& used,
              vector<int>& scc)
{
    used[x] = true;
    scc[x] = comp;

    for (int to: g[x]) {
        if (used[to])
            continue;

        find_scc(g, to, comp, used, scc);
    }
}

bool is_reachable(const graph& g, int x, int to, vector<bool>& used)
{
    if (x == to)
        return true;

    used[x] = true;

    for (int next: g[x]) {
        if (used[next])
            continue;
        
        if (is_reachable(g, next, to, used))
            return true;
    }

    return false;
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

    for (int i = 0; i < n; ++i)
        if (!used[i])
            find_order(g, i, used, order);

    reverse(order.begin(), order.end());

    fill(used.begin(), used.end(), false);
    int comp = 0;
    vector<int> scc(n, -1);

    for (int x: order) {
        if (used[x])
            continue;

        find_scc(rg, x, comp, used, scc);
        ++comp;
    }

    if (comp == 1) {
        cout << "YES" << endl;
        return 0;
    }

    cout << "NO" << endl;
    for (int i = 1; i < n; ++i) {
        if (scc[i] == scc[0])
            continue;

        fill(used.begin(), used.end(), false);
        if (!is_reachable(g, 0, i, used))
            cout << 1 << " " << i + 1 << endl;
            
        else
            cout << i + 1 << " " << 1 << endl;
        break;
    }

    return 0;
}
