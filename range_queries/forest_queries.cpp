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

ll safe_get(const vector<vector<ll>>& v, int i, int j)
{
    int x = v.size();
    if (0 <= i && i < x) {
        const vector<ll>& vv = v[i];

        int y = vv.size();
        if (0 <= j && j < y)
            return vv[j];
    }

    return 0;
}

ll get_sum(const vector<vector<ll>>& v, int i, int j)
{
    return safe_get(v, i, j);
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<vector<int>> forest(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        string line;
        cin >> line;

        for (int j = 0; j < n; ++j)
            forest[i][j] = (line[j] == '*');
    }

    vector<vector<ll> > p(n, vector<ll>(n));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            p[i][j] = forest[i][j] +
                      safe_get(p, i, j - 1) +
                      safe_get(p, i - 1, j) -
                      safe_get(p, i - 1, j - 1);

    for (int query = 0; query < q; ++query) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a, --b, --c, --d;

        ll x = get_sum(p, c, d);
        ll y = get_sum(p, a - 1, b - 1);
        ll z = get_sum(p, a - 1, d);
        ll w = get_sum(p, c, b - 1);

        ll r = x + y - z - w;

        cout << r << '\n';
    }

    return 0;
}
