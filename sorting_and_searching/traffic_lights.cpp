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
    int x, n;
    cin >> x >> n;

    set<int> b = {0, x};
    map<int, int> cnt;
    ++cnt[x];

    for (int i = 0; i < n; ++i) {
        int p = 0;
        cin >> p;
        auto pp = b.insert(p);
        auto it = pp.first;
        auto prev = it;
        --prev;

        auto next = it;
        next++;

        int len = *next - *prev;
        // cerr << len << '\n';

        auto len_it = cnt.find(len);
        --len_it->second;
        if (len_it->second == 0)
            cnt.erase(len_it);

        ++cnt[p - *prev];
        ++cnt[*next - p];
        cout << cnt.rbegin()->first << ' ';
    }

    cout << '\n';
    return 0;
}
