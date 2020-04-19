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

    set<int> used;
    used.insert(v[0]);
    int left = 0;
    int mx = 1;

    for (int i = 1; i < n; ++i) {
        while (used.count(v[i])) {
            used.erase(v[left]);
            ++left;
        }

        used.insert(v[i]);
        mx = max(mx, i - left + 1);
    }


    cout << mx << '\n';
    return 0;
}
