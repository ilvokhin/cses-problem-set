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
using tree = vector<vector<int>>;

void calc_subtree_size(const tree& t, int x, int p, vector<int>& subtree)
{
    subtree[x] = 1;

    for (int child: t[x]) {
        if (child == p)
            continue;
        calc_subtree_size(t, child, x, subtree);
        subtree[x] += subtree[child];
    }
}

int find_centroid(const tree& t, const vector<int>& subtree, int x, int p)
{
    const int n = t.size();
    for (int child: t[x]) {
        if (child == p)
            continue;
        if (2 * subtree[child] > n)
            return find_centroid(t, subtree, child, x);
    }

    return x;
}

int main()
{
    int n;
    cin >> n;

    tree t(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        t[a].push_back(b);
        t[b].push_back(a);
    }

    vector<int> subtree(n);
    calc_subtree_size(t, 0, -1, subtree);

    cout << find_centroid(t, subtree, 0, -1) + 1 << endl;

    return 0;
}
