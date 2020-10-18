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

vector<vector<int> > precalc(const vector<int>& seed, int k)
{
    int n = seed.size();
    vector<vector<int> > out(k, vector<int>(n));
    out[0] = seed;

    for (int i = 1; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            out[i][j] = out[i - 1][out[i - 1][j]];
        }
    }

    return out;
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        --v[i];
    }

    const vector<vector<int>> p = precalc(v, 30);

    for (int query = 0; query < q; ++query) {
        int x, k;
        cin >> x >> k;
        --x;

        for (int i = 0; i < 30; ++i) {
            if ((k >> i) & 1)
                x = p[i][x];
        }

        cout << x + 1 << endl;
    }

    return 0;
}
