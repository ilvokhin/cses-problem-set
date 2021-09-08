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

int combinations(int a, int b)
{
    static const vector<int> fact = calc_factorials(a + 1);
    int inv_a_b = fastexp(fact[a - b], MOD - 2);
    int inv_b = fastexp(fact[b], MOD - 2);
    return (((1LL * fact[a] * inv_a_b) % MOD) * inv_b) % MOD;
}

int main()
{
    int n, m;
    cin >> n >> m;

    cout << combinations(n + m - 1, m) << endl;

    return 0;
}
