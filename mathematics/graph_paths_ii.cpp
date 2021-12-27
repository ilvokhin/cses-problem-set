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
using matrix = vector<vector<ll>>;

const ll INF = numeric_limits<ll>::max();

matrix pseudomul(const matrix& a, const matrix& b) {
    assert(!a.empty() && !b.empty());
    assert(a[0].size() == b.size());

    int n = a.size();
    int m = b.size();
    int k = b[0].size();

    matrix out(n, vector<ll>(k, INF));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int x = 0; x < m; ++x) {
                if (a[i][x] == INF || b[x][j] == INF)
                    continue;

                out[i][j] = min(out[i][j], a[i][x] + b[x][j]);
            }
        }
    }

    return out;
}

matrix fastpow(const matrix& a, int n) {
    if (n == 1) {
        return a;
    }

    if (n % 2 == 0) {
        const matrix h = fastpow(a, n / 2);
        return pseudomul(h, h);
    }

    return pseudomul(a, fastpow(a, n - 1));
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    matrix g(n, vector<ll>(n, INF));

    for (int i = 0; i < m; ++i) {
        int x = 0, y = 0;
        ll w = 0;
        cin >> x >> y >> w;
        --x, --y;
        g[x][y] = min(g[x][y], w);
    }

    const matrix p = fastpow(g, k);
    const ll dist = p[0][n - 1];

    if (dist == INF) {
        cout << -1 << endl;
        return 0;
    }

    cout << dist << endl;

    return 0;
}
