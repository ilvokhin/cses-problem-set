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

struct kv {
    kv(ll value = 0, int idx = 0):
        value(value), idx(idx)
    { }

    ll value;
    int idx;
};

bool operator < (const kv& x, const kv& y)
{
    return x.value < y.value;
}

int main()
{
    int n, x;
    cin >> n >> x;

    vector<kv> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].value;
        v[i].idx = i + 1;
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll already = v[i].value + v[j].value;
            kv target(x - already);

            auto it = lower_bound(v.begin() + j + 1, v.end(), target);
            if (it == v.end() || it->value != target.value)
                continue;

            cout << v[i].idx << " " << v[j].idx << " " << it->idx << endl;
            return 0;
        }
    }

    cout << "IMPOSSIBLE" << endl;

    return 0;
}
