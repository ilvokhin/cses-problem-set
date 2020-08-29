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

    vector<string> grid(n);
    for (int i = 0; i < n; ++i)
        cin >> grid[i];

    if (grid[0][0] == '*') {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<ll> > dp(n, vector<ll>(n, 0));

    for (int i = 0; i < n; ++i) {
        if (grid[i][0] == '*')
            break;

        dp[i][0] = 1;
    }

    for (int j = 1; j < n; ++j) {
        if (grid[0][j] == '*')
            break;

        dp[0][j] = 1;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < n; ++j) {
            if (grid[i][j] == '*')
                continue;

            dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
        }
    }

    cout << dp[n - 1][n - 1] << endl;

    return 0;
}
