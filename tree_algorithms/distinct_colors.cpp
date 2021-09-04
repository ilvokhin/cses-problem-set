#include <unordered_set>
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

void merge_sets(unordered_set<int>& x, unordered_set<int>& y)
{
    if (x.size() < y.size())
        swap(x, y);

    for (int val: y)
        x.insert(val);
}

unordered_set<int> count_colors(const tree& t, const vector<int>& colors,
                                int x, int p, vector<int>& subtree)
{
    unordered_set<int> current = { colors[x] };

    for (int child: t[x]) {
        if (child == p)
            continue;

        auto child_colors = count_colors(t, colors, child, x, subtree);
        merge_sets(current, child_colors);
    }

    subtree[x] = current.size();
    return current;
}

int main()
{
    int n;
    cin >> n;

    vector<int> colors(n);
    for (int i = 0; i < n; ++i)
        cin >> colors[i];

    tree t(n);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        t[a].push_back(b);
        t[b].push_back(a);
    }

    vector<int> subtree(n);
    count_colors(t, colors, 0, -1, subtree);

    copy(subtree.begin(), subtree.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
