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
const ll INF = numeric_limits<ll>::max();

int main()
{
    ll n, x;
    cin >> n >> x;

    vector<ll> coins(n);
    for (int i = 0; i < n; ++i)
        cin >> coins[i];

    vector<ll> ncoins(x + 1, INF);
    ncoins[0] = 0;

    for (int i = 0; i < x + 1; ++i) {
        if (ncoins[i] == INF)
            continue;

        for (ll coin: coins)
            if (i + coin < x + 1)
                ncoins[i + coin] = min(ncoins[i + coin], ncoins[i] + 1);
    }

    if (ncoins[x] == INF) {
        cout << -1 << endl;
        return 0;
    }

    cout << ncoins[x] << endl;

    return 0;
}
