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

const int INF = numeric_limits<int>::max();

class min_segement_tree {
public:
    min_segement_tree(const vector<int>& v):
        n_(v.size())
    {
        assert(!v.empty());
        tree_.resize(4 * n_);
        build(v, 0, 0, n_ - 1);
    }

    int find_min(int l, int r) const
    {
        return find_min(0, 0, n_ - 1, l, r);
    }

    void update(int pos, int value)
    {
        return update(0, 0, n_ - 1, pos, value);
    }

private:
    void build(const vector<int>& v, int x, int l, int r)
    {
        if (l == r) {
            tree_[x] = v[l];
            return;
        }

        int m = (l + r) / 2;
        build(v, 2 * x + 1, l, m);
        build(v, 2 * x + 2, m + 1, r);

        tree_[x] = min(tree_[2 * x + 1], tree_[2 * x + 2]);
    }

    void update(int x, int l, int r, int pos, int value)
    {
        if (l == r) {
            tree_[x] = value;
            return;
        }

        int m = (l + r) / 2;
        if (pos <= m)
            update(2 * x + 1, l, m, pos, value);
        else
            update(2 * x + 2, m + 1, r, pos, value);

        tree_[x] = min(tree_[2 * x + 1], tree_[2 * x + 2]);
    }

    int find_min(int x, int tree_l, int tree_r, int l, int r) const
    {
        if (l > r)
            return INF;

        if (tree_l == l && tree_r == r)
            return tree_[x];

        int m = (tree_l + tree_r) / 2;

        int a = find_min(2 * x + 1, tree_l, m, l, min(r, m));
        int b = find_min(2 * x + 2, m + 1, tree_r, max(l, m + 1), r);

        return min(a, b);
    }

    int n_;
    vector<int> tree_;
};

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    min_segement_tree tree(v);

    for (int query = 0; query < q; ++query) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, val;
            cin >> x >> val;
            tree.update(x - 1, val);
        } else {
            int a, b;
            cin >> a >> b;
            --a, --b;
            cout << tree.find_min(a, b) << '\n';
        }
    }

    return 0;
}
