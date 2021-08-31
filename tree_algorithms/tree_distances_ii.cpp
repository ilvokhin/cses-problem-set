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

void init_values(const tree& t, int x, int p, ll dist,
                 vector<int>& subtree, vector<ll>& distances)
{
    distances[0] += dist;
    subtree[x] = 1;
    for (int child: t[x]) {
        if (child == p)
            continue;
        init_values(t, child, x, dist + 1, subtree, distances);
        subtree[x] += subtree[child];
    }
}

void calc_distances(const tree& t, vector<int>& subtree, int x, int p,
                    vector<ll>& distances)
{
    const int n = t.size();

    for (int child: t[x]) {
        if (child == p)
            continue;
        distances[child] = distances[x] + n - 2 * subtree[child];
        calc_distances(t, subtree, child, x, distances);
    }
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
    vector<ll> distances(n);

    init_values(t, 0, -1, 0, subtree, distances);
    calc_distances(t, subtree, 0, -1, distances);

    copy(distances.begin(), distances.end(), ostream_iterator<ll>(cout, " "));
    cout << endl;

    return 0;
}
