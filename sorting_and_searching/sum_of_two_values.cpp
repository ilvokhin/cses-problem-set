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

struct elem {
    ll val = 0;
    int idx = 0;
};

int main()
{
    int n;
    ll x;

    cin >> n >> x;

    vector<elem> v(n);

    for (int i = 0; i < n; ++i) {
        cin >> v[i].val;
        v[i].idx = i + 1;
    }

    sort(v.begin(), v.end(), [](const elem& x, const elem& y)
                             { return x.val < y.val; });

    int l = 0, r = n - 1;
    while (l < r) {
        ll s = v[l].val + v[r].val;

        if (s < x)
            ++l;
        else if(s > x)
            --r;
        else {
            cout << v[l].idx << ' ' << v[r].idx << '\n';
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";

    return 0;
}
