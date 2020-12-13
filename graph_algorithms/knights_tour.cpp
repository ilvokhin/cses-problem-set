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
// board size
const int N = 8;

struct pos {
    pos(int x, int y):
        x(x), y(y), used(0)
    { }

    int x;
    int y;
    int used;
};

struct Warnsdorff {
    Warnsdorff(const vector<vector<vector<pos>>>& possible):
        possible_(possible)
    { }

    bool operator()(const pos& a, const pos& b) const
    {
        int a_moves = possible_[a.x][a.y].size() - a.used;
        int b_moves = possible_[b.x][b.y].size() - b.used;

        if (a_moves == b_moves)
            return tie(a.x, a.y) < tie(b.x, b.y);

        return a_moves < b_moves;
    }

    const vector<vector<vector<pos>>>& possible_;
};

bool is_good(int x, int y)
{
    return 0 <= x && x < N && 0 <= y && y < N;
}

vector<pos> gen_moves(int x, int y)
{
    vector<pos> moves;

    static const int dx[] = {-2, -2, -1, +1, +2, +2, +1, -1};
    static const int dy[] = {-1, +1, +2, +2, +1, -1, -2, -2};

    for (int k = 0; k < 8; ++k) {
        int next_x = x + dx[k];
        int next_y = y + dy[k];

        if (!is_good(next_x, next_y))
            continue;

        moves.emplace_back(next_x, next_y);
    }

    return moves;
}

vector<vector<vector<pos>>> find_possible_moves()
{
    vector<vector<vector<pos>>> moves(N, vector<vector<pos>>(N));

    for (int x = 0; x < N; ++x)
        for (int y = 0; y < N; ++y)
            moves[x][y] = gen_moves(x, y);

    return moves;
}

bool go(int x, int y, const vector<vector<vector<pos>>>& possible_moves,
        vector<vector<bool>>& used, vector<pos>& moves)
{
    used[x][y] = true;
    moves.emplace_back(x, y);

    if (moves.size() == N * N)
        return true;

    vector<pos> next = gen_moves(x, y);
    for (pos& p: next) {
        for(const pos& np: possible_moves[p.x][p.y])
            if (used[np.x][np.y])
                ++p.used;
    }

    sort(next.begin(), next.end(), Warnsdorff(possible_moves));

    for (const pos& n: next) {
        if (used[n.x][n.y])
            continue;

        if (go(n.x, n.y, possible_moves, used, moves))
            return true;
    }

    moves.pop_back();
    used[x][y] = false;
    return false;
}

vector<pos> solve(int x, int y)
{
    vector<pos> moves;

    const vector<vector<vector<pos>>> possible_moves = find_possible_moves();
    vector<vector<bool>> used(N, vector<bool>(N));

    go(x, y, possible_moves, used, moves);

    return moves;
}

int main()
{
    int x, y;
    cin >> x >> y;
    --x, --y;

    const vector<pos> moves = solve(x, y);
    vector<vector<int>> board(N, vector<int>(N));

    for (size_t i = 0; i < moves.size(); ++i) {
        int x = moves[i].x;
        int y = moves[i].y;

        board[y][x] = i + 1;
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << board[i][j] << " ";
        cout << endl;
    }

    cout << endl;

    return 0;
}
