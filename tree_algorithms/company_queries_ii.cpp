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

void find_depth(const tree& t, int x, int d, vector<int>& depth)
{
    depth[x] = d;

    for (int child: t[x])
        find_depth(t, child, d + 1, depth);
}

int lift(const table& parents, int x, int k)
{
    static const int P = parents.size();

    for (int p = 0; p < P; ++p) {
        if ((1 << p) & k) {
            x = parents[p][x];
        }
    }

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

    static const int P = log2(n) + 1;

    table parents(P, vector<int>(n));
    tree t(n);

    for (int i = 1; i < n; ++i) {
        int x;
        cin >> x;
        --x;
        parents[0][i] = x;
        t[x].push_back(i);
    }

    for (int p = 1; p < P; ++p) {
        for (int i = 0; i < n; ++i) {
            int x = parents[p - 1][i];
            parents[p][i] = parents[p - 1][x];
        }
    }

    vector<int> depth(n);
    find_depth(t, 0, 0, depth);

    while (q--) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        int lca = find_lca(parents, depth, a, b);
        cout << lca + 1 << '\n';
    }

    return 0;
}
