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

using graph = vector<vector<int>>;

const int MOD = 1e9 + 7;

int solve(const graph& g)
{
    int n = g.size();
    int max_mask = (1ULL << n);

    vector<vector<int>> dp(max_mask, vector<int>(n));
    dp[1][0] = 1;

    for (int mask = 1; mask < max_mask; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (!(mask & (1ULL << last)))
                continue;

            if (dp[mask][last] == 0)
                continue;

            for (int to: g[last]) {
                int next_mask = (mask | (1ULL << to));

                if (mask == next_mask)
                    continue;

                dp[next_mask][to] += dp[mask][last];
                dp[next_mask][to] %= MOD;
            }
        }
    }

    return dp[max_mask - 1][n - 1];
}

int main()
{
    std::ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    graph g(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        g[a].push_back(b);
    }

    cout << solve(g) << endl;

    return 0;
}
