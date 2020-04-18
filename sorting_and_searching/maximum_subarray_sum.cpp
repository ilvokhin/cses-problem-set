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
    int n;
    cin >> n;

    vector<ll> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    ll cur = 0;
    ll mx = -INF;

    for (int i = 0; i < n; ++i) {
        cur += v[i];

        mx = max(mx, cur);
        if (cur < 0)
            cur = 0;
    }

    cout << mx << '\n';

    return 0;
}
