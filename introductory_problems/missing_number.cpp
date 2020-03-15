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

    ll actual_sum = 0;

    for (int i = 0; i < n - 1; ++i) {
        ll x;
        cin >> x;

        actual_sum += x;
    }

    ll expected_sum = 1ULL * n * (n + 1) / 2;

    cout << expected_sum - actual_sum << endl;

    return 0;
}
