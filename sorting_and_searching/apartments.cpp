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
    ll n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<int> b(m);
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll out = 0;
    int i = 0, j = 0;

    while (i < n && j < m) {
        if (abs(a[i] - b[j]) <= k) {
            ++out;
            ++i;
            ++j;
        } else if(a[i] < b[j]) {
            ++i;
        } else {
            ++j;
        }
    }

    cout << out << endl;

    return 0;
}
