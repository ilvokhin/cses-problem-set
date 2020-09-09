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

struct point {
    point(int x = 0, int y = 0):
        x(x), y(y)
    { }

    int x;
    int y;
};

bool operator == (const point& a, const point& b)
{
    return tie(a.x, a.y) == tie(b.x, b.y);
}

struct item {
    point p;
    string path;
};

bool is_valid(const point& p, int n, int m)
{
    return 0 <= p.x && p.x < n && 0 <= p.y && p.y < m;
}

bool go(const vector<string>& g, const point& begin, const point& end,
        string& path)
{
    int n = g.size();
    int m = g[0].size();

    vector<vector<bool> > used(n, vector<bool>(m));

    static int dx[] = {0, -1, 0, 1};
    static int dy[] = {-1, 0, 1, 0};
    static char dir[] = "LURD";

    queue<item> q;
    q.push({ begin, "" });
    used[begin.x][begin.y] = true;

    while (!q.empty()) {
        const item cur_item = q.front();
        const point cur = cur_item.p;
        q.pop();
   
        if (cur == end) {
            path = cur_item.path;
            return true;
        }

        for (int k = 0; k < 4; ++k) {
            point next(cur.x + dx[k], cur.y + dy[k]);

            if (!is_valid(next, n, m) || used[next.x][next.y])
                continue;

            if (g[next.x][next.y] == '#')
                continue;

            used[next.x][next.y] = true;
            q.push({ next, cur_item.path + dir[k] });
        }
    }

    return false;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<string> g(n);

    point begin;
    point end;

    for (int i = 0; i < n; ++i) {
        cin >> g[i];

        for (int j = 0; j < m; ++j) {
            if (g[i][j] == 'A')
                begin = { i, j };
            else if (g[i][j] == 'B')
                end = { i, j };
        }
    }

    string path;
    if (!go(g, begin, end, path)) {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    cout << path.size() << endl;
    cout << path << endl;

    return 0;
}
