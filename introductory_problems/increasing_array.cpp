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
    int n;
    cin >> n;

    vector<int> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    ll out = 0;

    for(int i = 1; i < n; ++i) {
        if (v[i - 1] <= v[i])
            continue;

        ll delta = v[i - 1] - v[i];
        out += delta;
        v[i] += delta;
    }

    cout << out << endl;

    return 0;
}
