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
    int t;
    cin >> t;

    while(t--) {
        ll a = 0, b = 0;
        cin >> a >> b;

        ll y = a - 2 * b;
        if (y % 3) {
            cout << "NO\n";
            continue;
        }

        y /= -3;

        ll x = a - y;
        if (x % 2) {
            cout << "NO\n";
            continue;
        }

        x /= 2;

        if (x < 0 || y < 0) {
            cout << "NO\n";
            continue;
        }

        cout << "YES\n";
    }

    return 0;
}
