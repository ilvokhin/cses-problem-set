#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <numeric>
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

bool can_divide(const vector<int>& v, int k, ll sum)
{
    int subarrays = 1;
    ll cur = 0;

    int n = v.size();
    for (int i = 0; i < n; ++i) {
        if (cur + v[i] <= sum) {
            cur += v[i];
            continue;
        }

        ++subarrays;
        cur = v[i];
    }

    return (subarrays <= k);
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    int mx = *max_element(v.begin(), v.end());
    ll sum = accumulate(v.begin(), v.end(), 0LL);

    ll l = mx, r = sum;

    while (l < r) {
        ll m = l + (r - l) / 2;

        if (can_divide(v, k, m))
            r = m;
        else
            l = m + 1;
    }

    cout << l << endl;

    return 0;
}
