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
using vs = vector<string>;
using vb = vector<bool>;
const int N = 8;

void go(const vs& f, int i, vb& col, vb& d1, vb& d2, ll& out)
{
    if (i == N) {
        ++out;
        return;
    }

    for (int j = 0; j < N; ++j) {
        if (col[j] || d1[i + j] || d2[j - i + N - 1])
            continue;

        if (f[i][j] == '*')
            continue;

        col[j] = d1[i + j] = d2[j - i + N - 1] = true;

        go(f, i + 1, col, d1, d2, out);

        col[j] = d1[i + j] = d2[j - i + N - 1] = false;
    }
}

int main()
{
    vs f(8);

    for (int i = 0; i < N; ++i)
        cin >> f[i];

    ll out = 0;
    vb col(N);
    vb d1(2*N);
    vb d2(2*N);

    go(f, 0, col, d1, d2, out);

    cout << out << '\n';

    return 0;
}
