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

struct job {
    int a = 0;
    int b = 0;
    ll p = 0;
};

bool operator < (const job& x, const job& y)
{
    return x.b < y.b;
}

int main()
{
    int n;
    cin >> n;

    vector<job> jobs(n);
    for (int i = 0; i < n; ++i)
        cin >> jobs[i].a >> jobs[i].b >> jobs[i].p;

    sort(jobs.begin(), jobs.end());

    map<int, ll> dp;
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        auto it = dp.lower_bound(jobs[i].a);
        --it;

        ll cur = it->second + jobs[i].p;
        auto prev = dp.upper_bound(jobs[i].b);
        --prev;
        dp[jobs[i].b] = max(prev->second, cur);
    }

    ll out = 0;
    for (const auto& kv: dp) {
        // cout << kv.first << " " << kv.second << endl;
        out = max(out, kv.second);
    }

    cout << out << endl;

    return 0;
}
