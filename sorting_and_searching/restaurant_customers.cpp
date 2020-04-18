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

struct border {
    ll val = 0;
    bool is_end = false;
};

bool operator < (const border& x, const border& y)
{
    return tie(x.val, x.is_end) < tie(y.val, y.is_end);
}

int main()
{
    int n;
    cin >> n;

    vector<border> v;
    v.reserve(2 * n);

    for (int i = 0; i < n; ++i) {
        border x;
        cin >> x.val;
        v.push_back(x);

        cin >> x.val;
        x.is_end = true;
        v.push_back(x);   
    }

    sort(v.begin(), v.end());

    ll mx = 0;
    ll cur = 0;
    for (const auto& b: v) {
        if (b.is_end) {
            --cur;
            continue;
        }

        ++cur;
        mx = max(mx, cur);
    }

    cout << mx << '\n';

    return 0;
}
