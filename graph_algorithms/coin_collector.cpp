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

void find_order(const graph& g, int x, vector<bool>& used,
                vector<int>& order)
{
    used[x] = true;

    for (int to: g[x]) {
        if (used[to])
            continue;

        find_order(g, to, used, order);
    }

    order.push_back(x);
}

void mark_scc(const graph& gr, int x, int comp, vector<bool>& used,
              vector<int>& scc)
{
    used[x] = true;
    scc[x] = comp;

    for (int to: gr[x]) {
        if (used[to])
            continue;

        mark_scc(gr, to, comp, used, scc);
    }
}

vector<int> find_scc(const graph& g, const graph& gr)
{
    int n = g.size();

    vector<bool> used(n);
    vector<int> order;

    for (int i = 0; i < n; ++i) {
        if (used[i])
            continue;

        find_order(g, i, used, order);
    }

    reverse(order.begin(), order.end());

    vector<int> scc(n, -1);
    fill(used.begin(), used.end(), false);
    int comp = 0;

    for (int i: order) {
        if (used[i])
            continue;

        mark_scc(gr, i, comp, used, scc);
        ++comp;
    }

    return scc;
}

graph find_condensate(const graph& g, const vector<int>& scc)
{
    int n = *max_element(scc.begin(), scc.end());

    graph cond(n + 1);

    for (size_t x = 0; x < g.size(); ++x) {
        for (int to: g[x]) {
            if (scc[x] == scc[to])
                continue;

            cond[scc[x]].push_back(scc[to]);
        }
    }

    return cond;
}

vector<ll> find_condensate_coins(const vector<int>& scc, const vector<ll>& coins)
{
    int n = *max_element(scc.begin(), scc.end());
    vector<ll> cond(n + 1);

    for (size_t x = 0; x < coins.size(); ++x)
        cond[scc[x]] += coins[x];

    return cond;
}

void find_max_coins(const graph& g, int x, const vector<ll>& coins,
                    vector<ll>& sum)
{
    sum[x] = coins[x];
    ll mx = 0;

    for (int to: g[x]) {
        if (sum[to] == 0)
            find_max_coins(g, to, coins, sum);

        mx = max(mx, sum[to]);
    }

    sum[x] += mx;
}

ll solve(const graph& g, const vector<ll>& coins)
{
    int n = g.size();

    vector<ll> sum(n, 0);

    for (int i = 0; i < n; ++i) {
        if (sum[i] != 0)
            continue;

        find_max_coins(g, i, coins, sum);
    }

    return *max_element(sum.begin(), sum.end());
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<ll> coins(n);
    for (int i = 0; i < n; ++i)
        cin >> coins[i];

    graph g(n);
    graph gr(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    const vector<int> scc = find_scc(g, gr);

    const graph cond = find_condensate(g, scc);
    const vector<ll> cond_coins = find_condensate_coins(scc, coins);

    cout << solve(cond, cond_coins) << endl;

    return 0;
}
