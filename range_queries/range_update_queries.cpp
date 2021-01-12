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

    void add(int pos, ll val)
    {
        add(0, 0, n_ - 1, pos, val);
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

        if (l == tree_l && r == tree_r)
            return tree_[x];

        int m = (tree_l + tree_r) / 2;

        ll a = find_sum(2 * x + 1, tree_l, m, l, min(r, m));
        ll b = find_sum(2 * x + 2, m + 1, tree_r, max(l, m + 1), r);

        return a + b;
    }

    void add(int x, int tree_l, int tree_r, int pos, ll val)
    {
        if (tree_l == tree_r) {
            tree_[x] += val;
            return;
        }

        int m = (tree_l + tree_r) / 2;
        if (pos <= m)
            add(2 * x + 1, tree_l, m, pos, val);
        else
            add(2 * x + 2, m + 1, tree_r, pos, val);

        tree_[x] = tree_[2 * x + 1] + tree_[2 * x + 2];
    }

private:
    int n_;
    vector<ll> tree_;
};

int main()
{
    int n, q;
    cin >> n >> q;

    vector<ll> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    vector<ll> delta(n);
    delta[0] = v[0];
    for (int i = 1; i < n; ++i)
        delta[i] = v[i] - v[i - 1];

    sum_segment_tree tree(delta);

    for (int query = 0; query < q; ++query) {
        int t;
        cin >> t;
        if (t == 1) {
            ll a, b, u;
            cin >> a >> b >> u;
            --a, --b;
            tree.add(a, u);
            if(b + 1 < n)
                tree.add(b + 1, -u);
        } else {
            int k;
            cin >> k;
            --k;
            cout << tree.find_sum(0, k) << endl;
        }
    }

    return 0;
}
