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

bool operator < (const point& a, const point& b)
{
    return tie(a.x, a.y) < tie(b.x, b.y);
}

bool is_valid(const point& p, int n, int m)
{
    return 0 <= p.x && p.x < n && 0 <= p.y && p.y < m;
}

string restore_path(const point& end, const point& begin,
                    const map<point, point>& parent)
{
    string path;
    point cur = end;

    while (!(cur == begin)) {
        auto it = parent.find(cur);
        assert(it != parent.end());

        point prev = it->second;
        if (prev.x == cur.x && prev.y - 1 == cur.y)
            path += 'L';
        else if (prev.x - 1 == cur.x && prev.y == cur.y)
            path += 'U';
        else if (prev.x == cur.x && prev.y + 1 == cur.y)
            path += 'R';
        else if(prev.x + 1 == cur.x && prev.y == cur.y)
            path += 'D';
        else
            assert(false);

        cur = prev;
    }

    reverse(path.begin(), path.end());
    return path;
}

bool go(const vector<string>& g, const point& begin, const point& end,
        string& path)
{
    int n = g.size();
    int m = g[0].size();

    vector<vector<bool> > used(n, vector<bool>(m));
    map<point, point> parent;

    static int dx[] = {0, -1, 0, 1};
    static int dy[] = {-1, 0, 1, 0};

    queue<point> q;
    q.push(begin);
    used[begin.x][begin.y] = true;

    while (!q.empty()) {
        const point cur = q.front();
        q.pop();
   
        if (cur == end) {
            path = restore_path(cur, begin, parent);
            return true;
        }

        for (int k = 0; k < 4; ++k) {
            point next(cur.x + dx[k], cur.y + dy[k]);

            if (!is_valid(next, n, m) || used[next.x][next.y])
                continue;

            if (g[next.x][next.y] == '#')
                continue;

            used[next.x][next.y] = true;
            parent[next] = cur;
            q.push(next);
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
