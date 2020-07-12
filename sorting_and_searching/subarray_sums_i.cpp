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
    int n, x;
    cin >> n >> x;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    ll out = 0;
    ll cur = 0;
    int right = 0;
    for (int left = 0; left < n; ++left) {
        if (right < left) {
            right = left;
            cur = 0;
        }

        while (cur < x && right < n) {
            cur += v[right];
            ++right;
        }

        if (cur == x)
            ++out;

        cur -= v[left];
    }

    cout << out << endl;

    return 0;
}
