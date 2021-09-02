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
using tree = vector<vector<int>>;
using table = vector<vector<int>>;

void find_depth(const tree& t, int x, int p, int d,
                vector<int>& parents, vector<int>& depth)
{
    depth[x] = d;
    parents[x] = p;

    for (int child: t[x]) {
        if (child == p)
            continue;
        find_depth(t, child, x, d + 1, parents, depth);
    }
}

int lift(const table& parents, int x, int k)
{
    static const int P = parents.size();

    for (int p = 0; p < P; ++p)
        if ((1 << p) & k)
            x = parents[p][x];
    return x;
}

int find_lca(const table& parents, const vector<int>& depth, int a, int b)
{
    if (depth[a] > depth[b])
        swap(a, b);

    b = lift(parents, b, depth[b] - depth[a]);
    if (a == b)
        return a;

    static const int P = parents.size();

    for (int p = P - 1; p >= 0; --p) {
        int pa = parents[p][a];
        int pb = parents[p][b];

        if (pa == pb)
            continue;

        a = pa;
        b = pb;
    }

    return parents[0][a];
}

int main()
{
    int n, q;
    cin >> n >> q;

    tree t(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        t[a].push_back(b);
        t[b].push_back(a);
    }

    static const int P = log2(n) + 1;
    table parents(P, vector<int>(n));
    vector<int> depth(n);
    find_depth(t, 0, -1, 0, parents[0], depth);
    parents[0][0] = 0;

    for (int p = 1; p < P; ++p)
        for (int i = 0; i < n; ++i)
            parents[p][i] = parents[p - 1][parents[p - 1][i]];

    while (q--) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        int lca = find_lca(parents, depth, a, b);
        cout << depth[a] + depth[b] - 2 * depth[lca] << '\n';
    }

    return 0;
}
