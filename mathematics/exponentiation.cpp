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

static const ll MOD = 1e9 + 7;

ll fastexp(ll a, ll b)
{
    if (b == 0)
        return 1;

    if (b % 2 == 0) {
        ll x = fastexp(a, b / 2);
        return (x * x) % MOD;
    }
    return (a * fastexp(a, b - 1)) % MOD;
}

int main()
{
    int n;
    cin >> n;

    while (n--) {
        ll a, b;
        cin >> a >> b;
        cout << fastexp(a, b) << '\n';
    }

    return 0;
}
