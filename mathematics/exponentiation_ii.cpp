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

int fastexp(int a, int b, int mod)
{
    if (b == 0)
        return 1;

    if (b % 2 == 0) {
        int x = fastexp(a, b / 2, mod);
        return (1LL * x * x) % mod;
    }

    return (1LL * a * fastexp(a, b - 1, mod)) % mod;
}

int exp(int a, int b, int c)
{
    // Fermat's little theorem
    const int x = fastexp(b, c, MOD - 1);
    return fastexp(a, x, MOD);
}

int main()
{
    int n;
    cin >> n;

    while (n--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << exp(a, b, c) << '\n';
    }

    return 0;
}
