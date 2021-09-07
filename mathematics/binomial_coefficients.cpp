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
static const int N = 1e6 + 1;

int fastpow(int a, int b)
{
    if (b == 0)
        return 1;

    if (b % 2 == 0) {
        int x = fastpow(a, b / 2);
        return (1ULL * x * x) % MOD;
    }

    return (1ULL * a * fastpow(a, b - 1)) % MOD;
}

vector<int> calc_factorials(int n)
{
    vector<int> f(n);
    f[0] = 1;

    for (int i = 1; i < n; ++i)
        f[i] = (1ULL * f[i - 1] * i) % MOD;

    return f;
}

int bincoef(int a, int b)
{
    static const vector<int> fact = calc_factorials(N);
    int inv_fact_b = fastpow(fact[b], MOD - 2);
    int inv_fact_a_b = fastpow(fact[a - b], MOD - 2);

    return (((1ULL * fact[a] * inv_fact_b) % MOD) * inv_fact_a_b) % MOD;
}

int main()
{
    int n;
    cin >> n;

    while (n--) {
        int a, b;
        cin >> a >> b;
        cout << bincoef(a, b) << '\n';
    }

    return 0;
}
