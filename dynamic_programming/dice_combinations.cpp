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
const ll MOD = 1e9 + 7;

int main()
{
    ll n;
    cin >> n;

    vector<ll> sum(n + 1);
    sum[0] = 1;

    for (int i = 0; i < n + 1; ++i) {
        if (sum[i] == 0)
            continue;

        for(int d = 1; d <= 6; ++d) {
            if (i + d < n + 1) {
                sum[i + d] += sum[i];
                sum[i + d] %= MOD;
            }
        }
    }

    cout << sum[n] << endl;

    return 0;
}
