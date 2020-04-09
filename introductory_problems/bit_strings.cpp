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

ll MOD = 1e9 + 7;

int main()
{
    ll n;
    cin >> n;

    ll out = 1;

    for (ll i = 0; i < n; ++i) {
        out *= 2;
        out %= MOD;
    }

    cout << out << endl;

    return 0;
}
