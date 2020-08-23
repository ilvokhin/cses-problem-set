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
    int n;
    cin >> n;

    ll sum = n * (n + 1) / 2;
    if (sum % 2 == 1) {
        cout << 0 << endl;
        return 0;
    }

    sum /= 2;

    vector<vector<ll> > dp(sum + 1, vector<ll>(n + 1));
    dp[0][0] = 1;

    for (ll s = 1; s < sum + 1; ++s) {
        for (ll i = 1; i < n + 1; ++i) {
            dp[s][i] = dp[s][i - 1];

            if (s - i >= 0) {
                dp[s][i] += dp[s - i][i - 1];
                dp[s][i] %= MOD;
            }
        }
    }

    cout << dp[sum][n] << endl;

    return 0;
}
