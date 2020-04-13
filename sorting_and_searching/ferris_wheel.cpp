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
    ll x;
    cin >> n >> x;

    vector<ll> p(n);
    for (int i = 0; i < n; ++i)
        cin >> p[i];

    sort(p.begin(), p.end());

    int left = 0, right = n - 1;
    ll out = 0;

    while (left <= right) {
        if (p[left] + p[right] <= x) {
            ++left;
            --right;
            ++out;
        } else {
            ++out;
            --right;
        }
    }

    cout << out << endl;

    return 0;
}
