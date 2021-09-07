#include <unordered_map>
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
using prime_divisors = unordered_map<ll, ll>;
static const ll MOD = 1e9 + 7;

int calc_divisors_number(const prime_divisors& d)
{
    ll n = 1LL;
    for (const auto& kv: d) {
        ll mul = kv.second + 1;
        n = (n * mul) % MOD;
    }
    return n;
}

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

// That function is tricky one
// Source of inspiration is here:
// https://usaco.guide/problems/cses-2182-divisor-analysis/solution/#product-of-divisors
ll calc_sum_of_divisors(const prime_divisors& d)
{
    ll sum = 1;
    for (const auto& kv: d) {
        ll p = kv.first;
        ll k = kv.second;

        ll num = fastexp(p, k + 1) - 1;
        // use modular multiplicative inverse here
        ll denum = fastexp(p - 1, MOD - 2);
        sum = (((sum * num) % MOD) * denum) % MOD;
    }

    return sum;
}

int calc_product_of_divisors(const prime_divisors& d)
{
    ll n = 1;
    ll dn = 1;
    for (const auto& kv: d) {
        ll p = kv.first;
        ll k = kv.second;
        ll prev = fastexp(n, k + 1);
        ll x = fastexp(p, k * (k + 1) / 2) % MOD;

        n = (prev * fastexp(x, dn)) % MOD;

        dn = dn * (k + 1) % (MOD - 1);
    }

    return n;
}

int main()
{
    int n;
    cin >> n;

    prime_divisors cnt;

    for (int i = 0; i < n; ++i) {
        ll x, k;
        cin >> x >> k;
        cnt[x] = k;
    }

    ll dn = calc_divisors_number(cnt);
    ll ds = calc_sum_of_divisors(cnt);
    ll dp = calc_product_of_divisors(cnt);

    cout << dn << ' ' << ds << ' ' << dp << '\n';

    return 0;
}
