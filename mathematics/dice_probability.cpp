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
using ld = long double;

int main()
{
    int n, a, b;
    cin >> n >> a >> b;

    vector<ld> prob(6 * n + 1);
    prob[0] = 1.0;

    for (int roll = 0; roll < n; ++roll) {
        vector<ld> next(6 * n + 1);
        for (int origin = 6 * n; origin >= 0; --origin) {
            if (prob[origin] == 0.0)
                continue;

            for (int x = 1; x <= 6; ++x) {
                if (origin + x > 6 * n + 1)
                    break;
                next[origin + x] += prob[origin] / 6.0;
            }
        }
        prob = next;
    }

    ld p = 0;
    for (int val = a; val < b + 1; ++val)
        p += prob[val];

    cout << fixed << setprecision(6) << p << endl;

    return 0;
}
