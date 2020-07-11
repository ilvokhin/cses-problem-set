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

    ll sum = 0;
    ll mx = 0;
    for (int i = 0; i < n; ++i) {
        ll x = 0;
        cin >> x;

        sum += x;
        mx = max(mx, x);
    }

    cout << max(2 * mx, sum) << endl;

    return 0;
}
