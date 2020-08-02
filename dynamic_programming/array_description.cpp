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
const ll MOD = 1e9 + 7;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<vector<ll> > dp(n, vector<ll>(m + 1));

    if (v[0] == 0) {
        for (int j = 1; j < m + 1; ++j)
            dp[0][j] = 1;
    } else {
        dp[0][v[0]] = 1;
    }

    for (int i = 1; i < n; ++i) {
        int x = v[i];

        if (x != 0) {
            ll l = dp[i - 1][x - 1];
            ll u = dp[i - 1][x];
            ll r = 0;

            if (x + 1 < m + 1)
                r = dp[i - 1][x + 1];

            dp[i][x] = (l + u + r) % MOD;
            continue;
        }

        for (int j = 1; j < m + 1; ++j) {
            ll l = dp[i - 1][j - 1];
            ll u = dp[i - 1][j];
            ll r = 0;

            if (j + 1 < m + 1)
                r = dp[i - 1][j + 1];

            dp[i][j] = (l + u + r) % MOD;
        }
    }

    ll sum = 0;
    for (int j = 0; j < m + 1; ++j)
        sum = (sum + dp[n - 1][j]) % MOD;

    cout << sum << endl;

    return 0;
}
