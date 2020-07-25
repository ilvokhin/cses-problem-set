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

vector<ll> calc_pref(const vector<int>& v)
{
    int n = v.size();
    vector<ll> p(n);
    p[0] = v[0];

    for (int i = 1; i < n; ++i)
        p[i] = p[i - 1] + v[i];

    return p;
}

ll find_min(const multiset<ll>& st)
{
    assert(!st.empty());

    return *st.begin();
}

int main()
{
    int n, a, b;
    cin >> n >> a >> b;

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<ll> p = calc_pref(v);
    multiset<ll> st;

    st.insert(p[0]);

    ll out = p[a - 1];
    for (int i = a; i < n; ++i) {
        ll left = find_min(st);

        // in case we still don't have enough elements in set
        if (i - b < 0)
            left = min(left, 0LL);

        ll cur = p[i] - left;
        out = max(out, cur);

        if (!st.empty() && i - b >= 0) {
            auto it = st.find(p[i - b]);
            st.erase(it);
        }

        st.insert(p[i - a + 1]);
    }

    cout << out << endl;

    return 0;
}
