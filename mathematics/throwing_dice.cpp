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

const ll MOD = 1e9 + 7;

matrix mul_mod(const matrix& a, const matrix& b) {
    assert(!a.empty() && !b.empty());
    assert(a[0].size() == b.size());

    const int n = a.size();
    const int m = b.size();
    const int k = b[0].size();

    matrix out(n, vector<ll>(k));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int x = 0; x < m; ++x) {
                out[i][j] += (a[i][x] * b[x][j]) % MOD;
                out[i][j] %= MOD;
            }
        }
    }

    return out;
}

matrix binpow(const matrix& a, ll n) {
    assert(n > 0);

    if (n == 1) {
        return a;
    }

    if (n % 2 == 0) {
        const matrix h = binpow(a, n / 2);
        return mul_mod(h, h);
    }

    return mul_mod(a, binpow(a, n - 1));
}

int main()
{
    ll n;
    cin >> n;

    const matrix init = {{1},
                         {1},
                         {2},
                         {4},
                         {8},
                         {16}};

    if (1ULL * n < init.size()) {
        cout << init[n][0] << endl;
        return 0;
    }

    const matrix X = {{0, 1, 0, 0, 0, 0},
                      {0, 0, 1, 0, 0, 0},
                      {0, 0, 0, 1, 0, 0},
                      {0, 0, 0, 0, 1, 0},
                      {0, 0, 0, 0, 0, 1},
                      {1, 1, 1, 1, 1, 1}};

    const matrix f = binpow(X, n);
    const matrix r = mul_mod(f, init);

    cout << r[0][0] << endl;

    return 0;
}
