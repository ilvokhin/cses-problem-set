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

void find_farest(const tree& t, int x, int p, vector<int>& dist, int d)
{
    dist[x] = d;
    for (int child: t[x]) {
        if (child == p)
            continue;
        find_farest(t, child, x, dist, d + 1);
    }
}

vector<int> find_dist(const tree& t, int from)
{
    int n = t.size();
    vector<int> dist(n, 0);
    find_farest(t, from, -1, dist, 0);
    return dist;
}

int find_farest_node(const tree& t, int from)
{
    const vector<int> dist = find_dist(t, from);
    auto f = max_element(dist.begin(), dist.end());
    return distance(dist.begin(), f);
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

    int a = find_farest_node(t, 0);
    int b = find_farest_node(t, a);

    const vector<int> da = find_dist(t, a);
    const vector<int> db = find_dist(t, b);

    for (int i = 0; i < n; ++i)
        cout << max(da[i], db[i]) << ' ';
    cout << endl;

    return 0;
}
