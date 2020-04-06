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

ll solve(int x, int y)
{
    ll mx = max(x, y);

    ll d = (mx - 1) * (mx - 1) + mx;

    ll delta = 1;
    if (mx % 2 == 0)
        delta = -1;

    if (x < mx)
        delta *= -1;

    ll add = abs(mx - x) + abs(mx - y);
    d += delta * add;

    return d;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i) {
        int y, x;
        cin >> y >> x;
        cout << solve(x, y) << '\n';
    }

    return 0;
}
