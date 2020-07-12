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

int main()
{
    int n, x;
    cin >> n >> x;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<ll> pref(n);
    pref[0] = v[0];

    for (int i = 1; i < n; ++i)
        pref[i] = pref[i - 1] + v[i];

    map<ll, int> cnt = {{0, 1}};
    ll out = 0;

    for (int i = 0; i < n; ++i) {
        ll target = pref[i] - x;

        auto it = cnt.find(target);
        if (it != cnt.end())
            out += it->second;

        ++cnt[pref[i]];
    }

    cout << out << endl;

    return 0;
}
