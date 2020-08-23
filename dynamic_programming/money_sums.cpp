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

    int sum = 0;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        sum += v[i];
    }

    vector<bool> dp(sum + 1);
    dp[0] = true;
    int cnt = 0;

    for (int x: v) {
        for (int s = sum; s >= 0; --s) {
            if(s - x < 0 || !dp[s - x] || dp[s])
                continue;

            dp[s] = true;
            ++cnt;           
        }
    }

    cout << cnt << endl;
    for (int i = 1; i < sum + 1; ++i)
        if (dp[i])
            cout << i << " ";
    cout << endl;

    return 0;
}
