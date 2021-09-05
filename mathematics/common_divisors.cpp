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
static const int N = 1e6 + 1;

void count_divisors(int x, vector<int>& cnt)
{
    for (int i = 1; 1LL * i * i <= x; ++i) {
        if (x % i)
            continue;
        int a = i;
        int b = x / i;
        ++cnt[a];
        if (a != b)
            ++cnt[b];
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int> cnt(N);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        count_divisors(x, cnt);
    }

    int mx = 1;
    for (int i = 2; i < N; ++i)
        if (cnt[i] >= 2)
            mx = i;

    cout << mx << endl;

    return 0;
}
