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
    int n;
    cin >> n;

    vector<ll> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    sort(v.begin(), v.end());

    ll m = -1;
    if (v.size() % 2)
        m = v[v.size() / 2];
    else
        m = (v[v.size() / 2] + v[v.size() / 2] + 1) / 2.;

    ll out = 0;

    for (ll x: v)
        out += abs(x - m);

    cout << out << endl;
    return 0;
}
