#include <unordered_map>
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
    std::ios::sync_with_stdio(false);

    int n, x;
    cin >> n >> x;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    map<ll, pair<int, int> > mp;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ll already = v[i] + v[j];
            ll target = x - already;

            auto it = mp.find(target);
            if (it == mp.end())
                continue;

            const auto& p = it->second;
            cout << p.first + 1 << " " << p.second + 1 << " "
                 << i + 1 << " " << j + 1 << endl;
            return 0;
        }

        for (int k = 0; k < i; ++k) {
            ll already = v[i] + v[k];
            mp[already] = {k, i};
        }
    }

    cout << "IMPOSSIBLE" << endl;
    return 0;
}
