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
using matrix = vector<vector<int>>;

const int MOD = 1e9 + 7;

matrix mul_mod(const matrix& a, const matrix& b) {
    assert(!a.empty() && !b.empty());
    assert(a[0].size() == b.size());

    const int n = a.size();
    const int m = b.size();
    const int k = b[0].size();

    matrix out(n, vector<int>(k));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int x = 0; x < m; ++x) {
                out[i][j] += (1LL * a[i][x] * b[x][j]) % MOD;
                out[i][j] %= MOD;
            }
        }
    }

    return out;
}

matrix fastpow(const matrix& m, int n) {
    assert(n > 0);

    if (n == 1) {
        return m;
    }

    if (n % 2 == 0) {
        const matrix h = fastpow(m, n / 2);
        return mul_mod(h, h);
    }

    return mul_mod(m, fastpow(m, n - 1));
}

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    matrix g(n, vector<int>(n));

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        ++g[x][y];
    }

    const matrix p = fastpow(g, k);

    cout << p[0][n - 1] << endl;

    return 0;
}
