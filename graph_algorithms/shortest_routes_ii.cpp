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
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll> > g(n, vector<ll>(n, INF));

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;

        if (c < g[a][b])
            g[a][b] = g[b][a] = c;
    }

    for (int i = 0; i < n; ++i)
        g[i][i] = 0;

    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (g[i][k] < INF && g[k][j] < INF)
                    g[i][j] = min(g[i][j], g[i][k] + g[k][j]);

    for (int query = 0; query < q; ++query) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        ll d = g[a][b];
        if (d == INF) {
            cout << -1 << endl;
            continue;
        }

        cout << d << endl;
    }

    return 0;
}
