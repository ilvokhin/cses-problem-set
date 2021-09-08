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
static const int N = 2e6 + 1;
static const int MOD = 1e9 + 7;

vector<int> calc_factorials(int n)
{
    vector<int> fact(n);
    fact[0] = 1;

    for (int i = 1; i < n; ++i)
        fact[i] = (1LL * fact[i - 1] * i) % MOD;

    return fact;
}

int fastexp(int a, int b)
{
    if (b == 0)
        return 1;

    if (b % 2 == 0) {
        int x = fastexp(a, b / 2);
        return (1LL * x * x) % MOD;
    }

    return (1LL * a * fastexp(a, b - 1)) % MOD;
}

int get_factorial(int n)
{
    static const vector<int> fact = calc_factorials(N);
    return fact[n];
}

int get_inv(int n)
{
    return fastexp(n, MOD - 2);
}

int combinations(int a, int b)
{
    int inv_a_b = get_inv(get_factorial(a - b));
    int inv_b = get_inv(get_factorial(b));

    return (((1LL * get_factorial(a) * inv_a_b) % MOD) * inv_b) % MOD;
}

int catalan(int n)
{
    return (1LL * get_inv(n + 1) * combinations(2 * n, n)) % MOD;
}

int main()
{
    int n;
    cin >> n;

    if (n % 2) {
        cout << 0 << endl;
        return 0;
    }

    cout << catalan(n / 2) << endl;

    return 0;
}
