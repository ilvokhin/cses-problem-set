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
const ll INF = numeric_limits<ll>::max();

int main()
{
    int n;
    cin >> n;

    vector<ll> v(n);
    for(int i = 0; i < n; ++i)
        cin >> v[i];

    // [i; j]
    vector<vector<ll>> dp(n, vector<ll>(n));

    for (int l = 0; l < n; ++l) {
        for (int i = 0; i + l < n; ++i) {
            ll x = -INF;
            {
                ll a = INF;
                if (i + 2 < n)
                    a = dp[i + 2][i + l];

                ll b = INF;
                if (i + 1 < n && i + l - 1 >= 0)
                    b = dp[i + 1][i + l - 1];

                x = v[i];
                if (min(a, b) != INF)
                    x += min(a, b);
            }

            ll y = -INF;
            {
                ll a = INF;
                if (i + 1 < n && i + l - 1 >= 0)
                    a = dp[i + 1][i + l - 1];

                ll b = INF;
                if (i + l - 2 >= 0)
                    b = dp[i][i + l - 2];

                y = v[i + l];
                if (min(a, b) != INF)
                    y += min(a, b);
            }

            dp[i][i + l] = max(x, y);
        }
    }

    cout << dp[0][n - 1] << endl;

    return 0;
}
