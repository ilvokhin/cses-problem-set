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
    int n, k;
    cin >> n >> k;

    vector<pair<int, int> > v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i].second >> v[i].first;

    sort(v.begin(), v.end());

    ll out = 0;
    multiset<int> used;
    for (int i = 0; i < k; ++i)
        used.insert(0);

    for (int i = 0; i < n; ++i) {
        int begin = v[i].second;
        int end = v[i].first;

        auto it = used.upper_bound(begin);
        if (it == used.begin())
            continue;

        --it;
        used.erase(it);
        ++out;
        used.insert(end);
    }

    cout << out << endl;

    return 0;
}
