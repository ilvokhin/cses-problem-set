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
    string a;
    string b;

    cin >> a >> b;

    int n = a.size();
    int m = b.size();

    vector<vector<int> > dp(n + 1, vector<int>(m + 1));

    for (int i = 0; i < n + 1; ++i)
        dp[i][0] = i;

    for (int j = 0; j < m + 1; ++j)
        dp[0][j] = j;

    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            char x = a[i - 1];
            char y = b[j - 1];

            dp[i][j] = min({ dp[i][j - 1] + 1,
                             dp[i - 1][j - 1] + (x != y),
                             dp[i - 1][j] + 1 } );
        }
    }

    cout << dp[n][m] << endl;

    return 0;
}
