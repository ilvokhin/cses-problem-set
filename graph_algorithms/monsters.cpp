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
using graph = vector<string>;

const int INF = numeric_limits<int>::max();

struct point {
    int x;
    int y;
};

bool operator != (const point& a, const point& b)
{
    return tie(a.x, a.y) != tie(b.x, b.y);
}

struct item {
    point p;
    int dist;
};

vector<point> gen_next(const point& seed)
{
    int dx[] = {-1, 0, 1, +0};
    int dy[] = {+0, 1, 0, -1};

    vector<point> out;

    for (int k = 0; k < 4; ++k) {
        int next_x = seed.x + dx[k];
        int next_y = seed.y + dy[k];

        out.push_back({next_x, next_y});
    }

    return out;
}

bool is_good(const point& p, int n, int m)
{
    return 0 <= p.x && p.x < n && 0 <= p.y && p.y < m;
}

void bfs(const graph& g, const vector<point>& start, vector<vector<int>>& dist,
         vector<vector<point>>& parent)
{
    int n = g.size();
    int m = g[0].size();

    dist = vector<vector<int>>(n, vector<int>(m, INF));
    parent = vector<vector<point>>(n, vector<point>(m, {-1, -1}));

    queue<item> q;

    for (const point& p: start) {
        q.push({p, 0});
        dist[p.x][p.y] = 0;
    }

    while (!q.empty()) {
        item cur = q.front();
        q.pop();

        for (const point& next: gen_next(cur.p)) {
            if (!is_good(next, n, m) || dist[next.x][next.y] != INF)
                continue;

            if (g[next.x][next.y] == '#')
                continue;

            dist[next.x][next.y] = cur.dist + 1;
            parent[next.x][next.y] = cur.p;
            q.push({next, dist[next.x][next.y]});
        }
    }
}

char get_motion(const point& cur, const point& prev)
{
    if (prev.x + 1 == cur.x && prev.y == cur.y)
        return 'D';
    else if (prev.x == cur.x && prev.y + 1 == cur.y)
        return 'R';
    else if (prev.x - 1 == cur.x && prev.y == cur.y)
        return 'U';
    else if (prev.x == cur.x && prev.y - 1 == cur.y)
        return 'L';

    assert(false);
    return '?';
}

string restore_path(const point& end, const point& start,
                    const vector<vector<point>>& parent)
{
    point cur = end;

    string path;

    while (cur != start) {
        assert(cur.x != -1 && cur.y != -1);

        char motion = get_motion(cur, parent[cur.x][cur.y]);
        path.push_back(motion);
        cur = parent[cur.x][cur.y];
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const point& end, const point& start,
                const vector<vector<point>>& parent)
{
    string path = restore_path(end, start, parent);

    cout << "YES" << endl;
    cout << path.size() << endl;
    cout << path << endl;
}

int main()
{
    int n, m;
    cin >> n >> m;

    graph g(n);

    point start;
    vector<point> monsters;

    for (int i = 0; i < n; ++i) {
        cin >> g[i];

        for (int j = 0; j < m; ++j) {
            if (g[i][j] == 'M')
                monsters.push_back({i, j});
            else if(g[i][j] == 'A')
                start = {i, j};
        }
    }

    vector<vector<int>> monsters_dist;
    vector<vector<point>> mp;
    bfs(g, monsters, monsters_dist, mp);

    vector<vector<int>> dist;
    vector<vector<point>> parent;
    bfs(g, { start }, dist, parent);

    for (int i = 0; i < n; ++i) {
        for (int j: {0, m - 1}) {
            if ((g[i][j] == '.' || g[i][j] == 'A') &&
                dist[i][j] < monsters_dist[i][j]) {
                print_path({i, j}, start, parent);
                return 0;
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        for (int i: {0, n - 1}) {
            if ((g[i][j] == '.' || g[i][j] == 'A') &&
                dist[i][j] < monsters_dist[i][j]) {
                print_path({i, j}, start, parent);
                return 0;
            }
        }
    }

    cout << "NO" << endl;

    return 0;
}
