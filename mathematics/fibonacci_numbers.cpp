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
static const int MOD = 1e9 + 7;

struct matrix {
public:
    matrix(ll a, ll b, ll c, ll d):
        a_(a), b_(b), c_(c), d_(d)
    { }

    matrix mul(const matrix& other) const {
        ll a = (a_ * other.a_ + b_ * other.c_) % MOD;
        ll b = (a_ * other.b_ + b_ * other.d_) % MOD;
        ll c = (c_ * other.a_ + d_ * other.c_) % MOD;
        ll d = (c_ * other.b_ + d_ * other.d_) % MOD;

        return matrix(a, b, c, d);
    }

    ll a_, b_;
    ll c_, d_;
};

matrix fastexp(const matrix& a, ll b)
{
    if (b == 0)
        return matrix(1, 0, 0, 1);

    if (b % 2 == 0) {
        matrix x = fastexp(a, b / 2);
        return x.mul(x);
    }

    return a.mul(fastexp(a, b - 1));
}

int fib(ll n)
{
    matrix init(0, 1, 1, 1);
    matrix f = fastexp(init, n);

    return f.b_;
}

int main()
{
    ll n;
    cin >> n;

    cout << fib(n) << endl;

    return 0;
}
