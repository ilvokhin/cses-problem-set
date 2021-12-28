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
    int n, a, b;
    cin >> n >> a >> b;

    vector<ll> ncount(6 * n + 1);
    ncount[0] = 1;

    for (int roll = 0; roll < n; ++roll) {
        vector<ll> next(6 * n + 1);
        for (int origin = 6 * n; origin >= 0; --origin) {
            if (ncount[origin] == 0)
                continue;

            for (int x = 1; x <= 6; ++x) {
                if (origin + x > 6 * n + 1)
                    break;
                next[origin + x] += ncount[origin];
            }
        }
        ncount = next;
    }

    ll num = 0;
    ll denum = 0;

    for (int i = 0; i < 6 * n + 1; ++i) {
        num += (a <= i && i <= b) ? ncount[i] : 0;
        denum += ncount[i];
    }

    cout << fixed << setprecision(6) << 1.0 * num / denum << endl;

    return 0;
}
