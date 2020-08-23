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
const int INF = numeric_limits<int>::max();

int main()
{
    int a, b;
    cin >> a >> b;

    vector<vector<int> > dp(a + 1, vector<int>(b + 1, INF));
    dp[0][0] = 0;

    for (int x = 1; x < a + 1; ++x) {
        for (int y = 1; y < b + 1; ++y) {
            if (x == y) {
                dp[x][y] = 0;
                continue;
            }

            for (int k = 1; k < x; ++k)
                dp[x][y] = min(dp[x][y], dp[k][y] + dp[x - k][y] + 1);

            for (int k = 1; k < y; ++k)
                dp[x][y] = min(dp[x][y], dp[x][k] + dp[x][y - k] + 1);
        }
    }

    cout << dp[a][b] << endl;

    return 0;
}
