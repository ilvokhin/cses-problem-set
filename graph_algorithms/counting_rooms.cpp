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

bool is_good(int x, int y, int n, int m)
{
    return 0 <= x && x < n && 0 <= y && y < m;
}

void dfs(const vector<string>& g, vector<vector<bool> >& used,
         int x, int y)
{
    used[x][y] = true;

    static const int dx[] = { 0, -1, 0, 1};
    static const int dy[] = {-1,  0, 1, 0};

    int n = g.size();
    int m = g[0].size();

    for (int k = 0; k < 4; ++k) {
        int next_x = x + dx[k];
        int next_y = y + dy[k];

        if (!is_good(next_x, next_y, n, m) ||
            used[next_x][next_y] ||
            g[next_x][next_y] != '.')
            continue;

        dfs(g, used, next_x, next_y);
    } 
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<string> v(n);

    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<vector<bool> > used(n, vector<bool>(m));

    ll rooms = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (v[i][j] == '.' && !used[i][j]) {
                dfs(v, used, i, j);
                ++rooms;
            }
        }
    }

    cout << rooms << endl;

    return 0;
}
