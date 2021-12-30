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
    int n, k;
    cin >> n >> k;

    vector<int> p(k);
    for (int i = 0; i < k; ++i)
        cin >> p[i];

    string state(n + 1, 'L');

    for (int i = 1; i < n + 1; ++i) {
        for (int x: p) {
            if (i - x < 0)
                continue;

            if (state[i - x] == 'L') {
                state[i] = 'W';
                break;
            }
        }
    }

    cout << state.substr(1) << endl;

    return 0;
}
