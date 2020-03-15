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
    string s;
    cin >> s;

    int n = s.size();

    int mx = 0;
    int cur = 0;
    char prev = '\0';

    for (int i = 0; i < n; ++i) {
        if (prev == s[i])
            ++cur;
        else
            cur = 1;

        mx = max(mx, cur);
        prev = s[i];
    }

    cout << mx << endl;

    return 0;
}
