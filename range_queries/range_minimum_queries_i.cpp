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

class min_sparse_table {
public:
    min_sparse_table(const vector<int>& v):
        k_(log2(v.size())),
        table_(k_ + 1, vector<int>()),
        logs_(v.size() + 1)
    {
        int n = v.size();

        logs_[1] = 0;

        for (int i = 2; i < n + 1; ++i)
            logs_[i] = logs_[i / 2] + 1;

        table_[0] = v;
        for (int j = 1; j < k_ + 1; ++j) {
            for (int i = 0; i + (1 << j) < n + 1; ++i) {
                int x = min(table_[j - 1][i], table_[j - 1][i + (1LL << (j - 1))]);
                table_[j].push_back(x);
            }
        }
    }

    // interval is inclusive [a; b]
    int find_min(int a, int b) const
    {
        int p = logs_[b - a + 1];
        int x = table_[p][a];
        int y = table_[p][b - (1 << p) +1];

        return min(x, y);
    }

private:
    int k_;
    vector<vector<int>> table_;
    vector<int> logs_;
};

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    min_sparse_table msp(v);

    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        cout << msp.find_min(a, b) << '\n';
    }

    return 0;
}
