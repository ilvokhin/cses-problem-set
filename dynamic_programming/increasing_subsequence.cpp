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

const int INF = numeric_limits<int>::max();

int main()
{
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<int> dp(n + 1, INF);
    dp[0] = -INF;

    for (int i = 0; i < n; ++i) {
        int x = v[i];

        auto it = lower_bound(dp.begin(), dp.end(), x);
        *it = x;
    }

    for (int i = n; i >= 0; --i)
        if (dp[i] != INF) {
            cout << i << endl;
            break;
        }

    return 0;
}
