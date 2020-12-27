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

ll find_sum(const vector<ll>& sum, int a, int b)
{
    if (a == 0)
        return sum[b];

    return sum[b] - sum[a - 1];
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<ll> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<ll> sum(n);
    sum[0] = v[0];

    for (int i = 1; i < n; ++i)
        sum[i] = sum[i - 1] + v[i];

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;

        --a, --b;
        cout << find_sum(sum, a, b) << '\n';
    }

    return 0;
}
