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
using table = vector<vector<int>>;

int main()
{
    int n, q;
    cin >> n >> q;

    static const int P = log2(n) + 1;

    table parents(P, vector<int>(n, -1));
    for (int i = 1; i < n; ++i) {
        cin >> parents[0][i];
        --parents[0][i];
    }

    for (int p = 1; p < P; ++p) {
        for (int i = 0; i < n; ++i) {
            int x = parents[p - 1][i];
            if (x == -1)
                continue;
            parents[p][i] = parents[p - 1][x];
        }
    }

    while (q--) {
        int x, k;
        cin >> x >> k;
        --x;

        for (int p = 0; p < P; ++p) {
            if (k & (1 << p)) {
                x = parents[p][x];
                if (x == -1)
                    break;
            }
        }
        cout << (x == -1 ? -1 : x + 1) << '\n';
    }

    return 0;
}
