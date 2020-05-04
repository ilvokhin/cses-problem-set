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

struct seg {
    int val;
    bool is_leaving;
    int idx;
};

bool operator < (const seg& x, const seg& y)
{
    return tie(x.val, x.is_leaving, x.idx) < tie(y.val, y.is_leaving, y.idx);
}

int main()
{
    int n;
    cin >> n;

    vector<seg> v;

    for (int i = 0; i < n; ++i) {
        int x = 0, y = 0;
        cin >> x >> y;

        v.push_back({x, false, i});
        v.push_back({y, true, i});
    }

    sort(v.begin(), v.end());

    vector<int> out(n, -1);
    int next = 1;
    set<int> already_free;

    for (const auto& e: v) {
        if (e.is_leaving) {
            already_free.insert(out[e.idx]);
            continue;
        }

        if (!already_free.empty()) {
            int cur = *(already_free.begin());
            already_free.erase(cur);
            out[e.idx] = cur;
            continue;
        }

        out[e.idx] = next;
        ++next;
    }

    cout << next - 1 << '\n';
    copy(out.begin(), out.end(), ostream_iterator<int>(cout, " "));
    cout << '\n';

    return 0;
}
