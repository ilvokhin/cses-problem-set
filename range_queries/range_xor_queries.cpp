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

class xor_segment_tree {
public:
    xor_segment_tree(const vector<int>& v):
        n_(v.size())
    {
        tree_.resize(4 * n_);
        build(v, 0, 0, n_ - 1);
    }

    int find_xor(int l, int r) const
    {
        return find_xor(0, 0, n_ - 1, l, r);
    }

private:
    void build(const vector<int>& v, int x, int tree_l, int tree_r)
    {
        if (tree_l == tree_r) {
            tree_[x] = v[tree_l];
            return;
        }

        int m = (tree_l + tree_r) / 2;
        build(v, 2 * x + 1, tree_l, m);
        build(v, 2 * x + 2, m + 1, tree_r);

        tree_[x] = tree_[2 * x + 1] ^ tree_[2 * x + 2];
    }

    int find_xor(int x, int tree_l, int tree_r, int l, int r) const
    {
        if (l > r)
            return 0;

        if (tree_l == l && tree_r == r)
            return tree_[x];

        int m = (tree_l + tree_r) / 2;

        int a = find_xor(2 * x + 1, tree_l, m, l, min(m, r));
        int b = find_xor(2 * x + 2, m + 1, tree_r, max(m + 1, l), r);

        return a ^ b;
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

    xor_segment_tree tree(v);

    for (int query = 0; query < q; ++query) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        cout << tree.find_xor(a, b) << '\n';
    }

    return 0;
}
