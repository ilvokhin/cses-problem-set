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
using point = pair<int, int>;
using mb = vector<vector<char>>;

const int N = 7;

bool is_good(const point& p)
{
    return 0 <= p.first && p.first < N &&
           0 <= p.second && p.second < N;
}

bool not_used(const mb& used, const point& p)
{
    int x = p.first;
    int y = p.second;

    return used[x][y];
}

void go(const string& s, mb& used, size_t pos, const point& p,
        int& out)
{
    int x = p.first;
    int y = p.second;

    if (pos >= s.size()) {
        if (p.first == N - 1 && p.second == 0)
            ++out;

        return;
    }

    if (x == N - 1 && y == 0)
        return;

    // Thats's kind of magic, that I don't really understand.

    // Check cases like that:
    //  |o
    // x|cx
    //  |o
    //
    //  o|
    // xc|x
    //  o|
    if (((is_good({x + 1, y}) && used[x + 1][y]) || x == N - 1) &&
        ((is_good({x - 1, y}) && used[x - 1][y]) || x == 0) &&
         y > 0 && y < N - 1 && !used[x][y - 1] && !used[x][y + 1])
        return;

    if (((is_good({x, y + 1}) && used[x][y + 1]) || y == N - 1) &&
        ((is_good({x, y - 1}) && used[x][y - 1]) || y == 0) &&
         x > 0 && x < N - 1 && !used[x - 1][y] && !used[x + 1][y])
        return;

    used[x][y] = true;

    if (s[pos] == '?' || s[pos] == 'D') {
        point next = {x + 1, y};
        if (is_good(next) && !not_used(used, next))
            go(s, used, pos + 1, next, out);
    }

    if (s[pos] == '?' || s[pos] == 'U') {
        point next = {x - 1, y};
        if (is_good(next) && !not_used(used, next))
            go(s, used, pos + 1, next, out);
    }

    if (s[pos] == '?' || s[pos] == 'L') {
        point next = {x, y - 1};
        if (is_good(next) && !not_used(used, next))
            go(s, used, pos + 1, next, out);
    }

    if (s[pos] == '?' || s[pos] == 'R') {
        point next = {x, y + 1};
        if (is_good(next) && !not_used(used, next))
            go(s, used, pos + 1, next, out);
    }

    used[x][y] = false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int out = 0;
    point p = {0, 0};

    mb used(N, vector<char>(N));

    go(s, used, 0, p, out);

    cout << out << endl;

    return 0;
}
