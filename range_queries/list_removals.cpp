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

class sum_segment_tree {
public:
    sum_segment_tree(const vector<ll>& v):
        n_(v.size()),
        tree_(4 * n_)
    {
        build(v, 0, 0, n_ - 1);
    }

    ll find_sum(int l, int r) const
    {
        return find_sum(0, 0, n_ - 1, l, r);
    }

    void update(int pos, int val)
    {
        update(0, 0, n_ - 1, pos, val);
    }

private:
    void build(const vector<ll>& v, int x, int l, int r)
    {
        if (l == r) {
            tree_[x] = v[l];
            return;
        }

        int m = (l + r) / 2;

        build(v, 2 * x + 1, l, m);
        build(v, 2 * x + 2, m + 1, r);

        tree_[x] = tree_[2 * x + 1] + tree_[2 * x + 2];
    }

    ll find_sum(int x, int tree_l, int tree_r, int l, int r) const
    {
        if (l > r)
            return 0;

        if (tree_l == l && tree_r == r)
            return tree_[x];

        int m = (tree_l + tree_r) / 2;
        ll a = find_sum(2 * x + 1, tree_l, m, l, min(r, m));
        ll b = find_sum(2 * x + 2, m + 1, tree_r, max(l, m + 1), r);

        return a + b;
    }

    void update(int x, int l, int r, int pos, int val)
    {
        if (l == r) {
            tree_[x] = val;
            return;
        }

        int m = (l + r) / 2;
        if (pos <= m)
            update(2 * x + 1, l, m, pos, val);
        else
            update(2 * x + 2, m + 1, r, pos, val);

        tree_[x] = tree_[2 * x + 1] + tree_[2 * x + 2];
    }

private:
    int n_;
    vector<ll> tree_;
};

int find_val(const sum_segment_tree& tree, int pos, int n)
{
    int l = 0, r = n - 1;

    while (l < r) {
        int m = l + (r - l) / 2;
        if (tree.find_sum(0, m) >= pos)
            r = m;
        else
            l = m + 1;
    }

    return l;
}

int main()
{
    int n;
    cin >> n;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<ll> present(n, 1);
    sum_segment_tree tree(present);

    vector<int> out;
    out.reserve(n);

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;

        int p = find_val(tree, x, n);
        out.push_back(v[p]);
        tree.update(p, 0);
    }

    copy(out.begin(), out.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
