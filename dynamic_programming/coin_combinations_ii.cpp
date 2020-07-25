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
    int n, x;
    cin >> n >> x;

    vector<ll> coins(n);
    for (int i = 0; i < n; ++i)
        cin >> coins[i];

    vector<ll> cnt(x + 1);
    cnt[0] = 1;

    for (ll coin: coins) {
        for (int i = 0; i < x + 1; ++i) {
            if (i + coin < x + 1) {
                cnt[i + coin] += cnt[i];
                cnt[i + coin] %= MOD;
            }
        }
    }

    cout << cnt[x] << endl;

    return 0;
}
