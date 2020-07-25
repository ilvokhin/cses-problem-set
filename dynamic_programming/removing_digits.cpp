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
const int INF = numeric_limits<int>::max();

vector<int> get_digits(int x)
{
    vector<int> out;

    while (x) {
        out.push_back(x % 10);
        x /= 10;
    }

    return out;
}

int main()
{
    int n;
    cin >> n;

    vector<int> cnt(n + 1, INF);
    cnt[n] = 0;

    for (int i = n; i >= 0; --i) {
        if (cnt[i] == INF)
            continue;

        for (int d: get_digits(i))
            if (i - d >= 0)
                cnt[i - d] = min(cnt[i - d], cnt[i] + 1);
    }

    cout << cnt[0] << endl;

    return 0;
}
