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
    int n, m;
    cin >> n >> m;

    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        int x = 0;
        cin >> x;
        ++cnt[x];
    }

    int p = 0;
    for (int i = 0; i < m; ++i) {
        cin >> p;

        auto it = cnt.upper_bound(p);
        if (it == cnt.begin()) {
            cout << -1 << '\n';
            continue;
        }

        --it;

        cout << it->first << '\n';

        --(it->second);
        if (it->second == 0)
            cnt.erase(it);
    }

    return 0;
}
