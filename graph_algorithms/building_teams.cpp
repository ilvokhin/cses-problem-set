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
using graph = vector<vector<int>>;

enum team: int {
    UNKNOWN = 0,
    A = 1,
    B = 2
};

team switch_team(const team& t)
{
    assert(t != UNKNOWN);

    if (t == A)
        return B;
    return A;
}

bool dfs(const graph& g, int x, const team& t, vector<team>& teams)
{
    teams[x] = t;

    for (int to: g[x]) {
        if (teams[to] == t)
            return false;
        else if (teams[to] == switch_team(t))
            continue;

        if(!dfs(g, to, switch_team(t), teams))
            return false;
    }

    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        g[a].push_back(b);
        g[b].push_back(a);
    }   

    vector<team> teams(n, UNKNOWN);

    for (int i = 0; i < n; ++i) {
        if (teams[i] != UNKNOWN)
            continue;

        if (!dfs(g, i, A, teams)) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    copy(teams.begin(), teams.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
