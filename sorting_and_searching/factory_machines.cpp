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

bool can_make(ll t, const vector<int>& v, ll products)
{
    int n = v.size();

    for (int i = 0; i < n; ++i) {
        products -= t / v[i];

        if (products <= 0)
            break;
    }

    
    return (products <= 0);
}

int main()
{
    int n;
    ll t;
    cin >> n >> t;

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    sort(v.begin(), v.end());

    ll l = 1, r = (t * v[n - 1]);

    while (l < r) {
        ll m = l + (r - l) / 2;

        if (can_make(m, v, t))
            r = m;
        else
            l = m + 1;
    }

    cout << l << endl;

    return 0;
}
