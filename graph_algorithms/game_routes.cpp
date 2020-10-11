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

ll solve(const graph& g, int x, vector<bool>& used, vector<ll>& cnt)
{
    int n = g.size();

    used[x] = true;

    if (x == n - 1) {
        cnt[x] = 1;
        return cnt[x];
    }

    for (int to: g[x]) {
        if (!used[to])
            solve(g, to, used, cnt);

        cnt[x] = (cnt[x] + cnt[to]) % MOD;
    }

    return cnt[x];
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        g[a].push_back(b);
    }

    vector<ll> cnt(n, 0);
    vector<bool> used(n);

    cout << solve(g, 0, used, cnt) << endl;

    return 0;
}
