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

struct task {
    ll duration;
    ll deadline;
};

bool operator < (const task& x, const task& y)
{
    return tie(x.duration, x.deadline) < tie(y.duration, y.deadline);
}

int main()
{
    int n;
    cin >> n;

    vector<task> v;
    v.reserve(n);

    for (int i = 0; i < n; ++i) {
        ll dur = 0, dead = 0;
        cin >> dur >> dead;

        v.push_back({dur, dead});
    }

    sort(v.begin(), v.end());

    ll reward = 0;
    ll t = 0;

    for (int i = 0; i < n; ++i) {
        t += v[i].duration;
        reward += v[i].deadline - t;
    }

    cout << reward << endl;

    return 0;
}
