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
using graph = vector<vector<int>>;

const ll MOD = 1e9 + 7;

ll solve(const graph& g)
{
    int n = g.size();
    ll max_mask = (1ULL << n);

    vector<vector<ll>> dp(n, vector<ll>(max_mask));
    dp[0][1] = 1;

    for (ll mask = 1; mask < max_mask; ++mask) {
        for (int last = 0; last < n; ++last) {
            if (!(mask & (1ULL << last)))
                continue;

            for (int to: g[last]) {
                ll next_mask = (mask | (1ULL << to));

                if (mask == next_mask)
                    continue;

                dp[to][next_mask] = (dp[to][next_mask] + dp[last][mask]) % MOD;
            }
        }
    }

    return dp[n - 1][max_mask - 1];
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
