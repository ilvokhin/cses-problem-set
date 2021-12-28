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
using ld = long double;

ld fastpow(ld a, int n) {
    if (n == 1) {
        return a;
    }

    if (n % 2 == 0) {
        const ld h = fastpow(a, n / 2);
        return h * h;
    }

    return a * fastpow(a, n - 1);
}

int main()
{
    int n, k;
    cin >> n >> k;

    ld e = 0.0;
    for (int x = 1; x < k + 1; ++x) {
        const ld gex = fastpow(1.0 * x / k, n);
        const ld lx = fastpow(1.0 * (x - 1) / k, n);
        e += (gex - lx) * x;
    }

    cout << fixed << setprecision(6) << e << endl;

    return 0;
}
