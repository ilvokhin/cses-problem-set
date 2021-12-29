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
    int n;
    cin >> n;

    vector<int> r(n);
    for (int i = 0; i < n; ++i)
        cin >> r[i];

    ld e = 0.0;
    for (int i = 0; i < n; ++i) {
        for (int val = 1; val < r[i] + 1; ++val) {
            for (int j = i + 1; j < n; ++j) {
                ld P = 0.0;
                if (r[j] < val) {
                    P = 1.0 / r[i];
                } else {
                    P = (1.0 / r[i]) * (val - 1) / r[j];
                }
                e += P;
            }
        }
    }

    cout << fixed << setprecision(6) << e << endl;

    return 0;
}
