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
using ld = long double;
using matrix = vector<vector<ld>>;

static const int N = 8;
static const vector<int> dr = {+0, +0, +1, -1};
static const vector<int> dc = {-1, +1, +0, +0};

bool is_good(int x, int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

int count_good_directions(int row, int col) {
    int directions = 0;

    for (size_t k = 0; k < dr.size(); ++k) {
        int next_row = row + dr[k];
        int next_col = col + dc[k];
        directions += is_good(next_row, next_col);
    }

    return directions;
}

matrix find_robot_final_prob(int x, int y, int steps) {
    matrix prob(N, vector<ld>(N));
    prob[x][y] = 1.0;

    for (int step = 0; step < steps; ++step) {
        matrix next(N, vector<ld>(N));

        for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
                if (prob[row][col] == 0.0)
                    continue;

                int directions = count_good_directions(row, col);

                for (size_t k = 0; k < dr.size(); ++k) {
                    int next_row = row + dr[k];
                    int next_col = col + dc[k];

                    if (!is_good(next_row, next_col))
                        continue;

                    next[next_row][next_col] += prob[row][col] / directions;
                }
            }
        }
        prob = next;
    }

    return prob;
}

void update(matrix& prob_empty, const matrix& robot) {
    for (int row = 0; row < N; ++row)
        for (int col = 0; col < N; ++col)
            prob_empty[row][col] *= (1.0 - robot[row][col]);
}

int main()
{
    int k;
    cin >> k;

    matrix prob_empty(N, vector<ld>(N, 1.0));

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            const matrix current = find_robot_final_prob(row, col, k);
            update(prob_empty, current);
        }
    }

    ld P = 0.0;
    for (int row = 0; row < N; ++row)
        for (int col = 0; col < N; ++col)
            P += prob_empty[row][col];

    cout << fixed << setprecision(6) << P << endl;

    return 0;
}
