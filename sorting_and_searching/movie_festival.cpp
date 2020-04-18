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

struct movie {
    int a = 0;
    int b = 0;
};

bool operator < (const movie& x, const movie& y)
{
    if (x.b != y.b)
        return x.b < y.b;

    return x.a > y.a;
}

int main()
{
    int n;
    cin >> n;

    vector<movie> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i].a >> v[i].b;

    sort(v.begin(), v.end());

    ll out = 0;
    int last = 0;
    for (int i = 0; i < n; ++i) {
        if (last > v[i].a)
            continue;

        ++out;
        last = v[i].b;
    }

    cout << out << '\n';

    return 0;
}
