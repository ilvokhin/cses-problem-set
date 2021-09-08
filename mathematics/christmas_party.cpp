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
static const int MOD = 1e9 + 7;

int count_derangements(int n)
{
    vector<int> d(n + 1);
    d[0] = 1;
    d[1] = 0;

    for (int i = 2; i < n + 1; ++i)
        d[i] = (((1LL * (i - 1)) % MOD) * (d[i - 2] + d[i - 1]) % MOD);

    return d[n];
}

int main()
{
    int n;
    cin >> n;

    cout << count_derangements(n) << endl;

    return 0;
}
