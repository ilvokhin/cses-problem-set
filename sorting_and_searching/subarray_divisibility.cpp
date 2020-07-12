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

int update(const map<ll, int>& cnt, ll rem)
{
    auto it = cnt.find(rem);
    if (it == cnt.end())
        return 0;

    return it->second;
}

int main()
{
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<ll> p(n);
    p[0] = v[0];

    for (int i = 1; i < n; ++i)
        p[i] = p[i - 1] + v[i];

    ll out = 0;
    map<ll, int> cnt = {{0, 1}};

    for (int i = 0; i < n; ++i) {
        ll x = p[i];

        ll r1 = (x % n + n) % n;
        ll r2 = (n - r1);

        out += update(cnt, r1);
        out += update(cnt, -r2);

        ++cnt[r1];
    }

    cout << out << endl;

    return 0;
}
