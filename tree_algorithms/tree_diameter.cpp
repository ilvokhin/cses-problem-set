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

void calc_dist(const tree& t, int node, int parent, vector<int>& dist, int d)
{
    dist[node] = d;
    for (int child: t[node]) {
        if (child == parent)
            continue;
        calc_dist(t, child, node, dist, d + 1);
    }
}

int find_diameter(const tree& t)
{
    int n = t.size();
    vector<int> dist(n, 0);

    calc_dist(t, 0, -1, dist, 0);

    auto farest = max_element(dist.begin(), dist.end());
    int f = distance(dist.begin(), farest);
    fill(dist.begin(), dist.end(), 0);

    calc_dist(t, f, -1, dist, 0);
    return *max_element(dist.begin(), dist.end());
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

    cout << find_diameter(t) << endl;

    return 0;
}
