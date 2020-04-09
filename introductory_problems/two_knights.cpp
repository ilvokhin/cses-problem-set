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

int main()
{
    ll n;
    cin >> n;

    cout << 0 << '\n';

    for (ll k = 2; k <= n; ++k) {
        ll all = (k * k) * (k * k - 1) / 2;
        ll attack = 2 * 2 * (k - 1) * (k - 2);

        cout << all - attack << '\n';
    }

    return 0;
}
