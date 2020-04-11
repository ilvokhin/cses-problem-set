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

const ll INF = numeric_limits<ll>::max();

int get_bit(uint64_t mask, int i)
{
    return (mask >> i) & 1;
}

int main()
{
    int n;
    cin >> n;

    vector<ll> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    ll mn = INF;

    for (uint64_t mask = 0; mask < (1ULL << n); ++mask) {
        ll x = 0;
        ll y = 0;

        for (int i = 0; i < n; ++i) {
            if (get_bit(mask, i))
                x += v[i];
            else
                y += v[i];
        }

        mn = min(mn, abs(x - y));
    }

    cout << mn << endl;

    return 0;
}
