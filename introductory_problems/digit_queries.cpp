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
static const int N = 19;

int get_digit(ll n, int d)
{
    string s = to_string(n);
    return s[d] - '0';
}

vector<ll> get_powers(int n)
{
    vector<ll> powers(n);
    powers[0] = 1;
    for (int i = 1; i < n; ++i)
        powers[i] = powers[i - 1] * 10;
    return powers;
}

ll get_pow10(int n)
{
    static const vector<ll> powers = get_powers(N);
    return powers.at(n);
}

ll calc_numbers_num(int digits)
{
    if (digits == 1)
        return 10;

    return get_pow10(digits) - get_pow10(digits - 1);
}

int solve(ll n)
{
    ll x = 0;
    ll len = 0;
    int digits = 1;
    for (; ; ++digits) {
        const ll numbers = calc_numbers_num(digits);
        const ll delta = digits * numbers;
        if (len + delta > n)
            break;
        x += numbers;
        len += delta;
    }

    const ll numbers = (n - len) / digits;
    x += numbers;
    const ll delta = numbers * digits;
    len += delta;

    return get_digit(x, n - len);
}

int main()
{
    int q;
    cin >> q;

    while (q--) {
        ll n;
        cin >> n;
        cout << solve(n) << '\n';
    }

    return 0;
}
