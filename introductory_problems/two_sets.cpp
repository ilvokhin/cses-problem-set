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

void pr(const vector<ll>& v)
{
    cout << v.size() << '\n';
    copy(v.begin(), v.end(), ostream_iterator<ll>(cout, " "));
    cout << '\n';
}

int main()
{
    ll n;
    cin >> n;

    ll sum = n * (n + 1) / 2;

    if (sum % 2 == 1) {
        cout << "NO\n";
        return 0;
    }

    sum /= 2;

    vector<bool> used(n + 1);

    for (ll i = n; i >= 1; i--) {
        if (sum - i > 0) {
            sum -= i;
            used[i] = true;
            continue;
        }

        break;
    }

    used[sum] = true;

    vector<ll> a;
    vector<ll> b;

    for(ll i = 1; i <= n; ++i) {
        if (used[i])
            a.push_back(i);
        else
            b.push_back(i);
    }

    cout << "YES\n";
    pr(a);
    pr(b);

    return 0;
}
