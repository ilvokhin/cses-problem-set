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

int main()
{
    int n, x;
    cin >> n >> x;

    vector<int> prices(n);
    vector<int> pages(n);

    for (int i = 0; i < n; ++i)
        cin >> prices[i];

    for (int i = 0; i < n; ++i)
        cin >> pages[i];

    vector<vector<ll> > dp(2, vector<ll>(x + 1));

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < x + 1; ++j) {
            dp[1][j] = dp[0][j];

            ll price = prices[i - 1];

            if (j - price >= 0)
                dp[1][j] = max(dp[1][j], dp[0][j - price] + pages[i - 1]);
        }

        for(int j = 1; j < x + 1; ++j)
            dp[0][j] = dp[1][j];
    }

    cout << dp[0][x] << endl;

    return 0;
}
