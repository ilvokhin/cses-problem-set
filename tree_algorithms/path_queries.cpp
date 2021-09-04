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
using tree = vector<vector<int>>;

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

class path {
public:
    path(const tree& t, const vector<ll>& values):
        index_(t.size()),
        values_(values)
    {
        vector<ll> sums;
        dfs(t, values, 0, -1, 0, sums);

        const int n = t.size();

        vector<ll> deltas(n);
        deltas[0] = sums[0];
        for (int i = 1; i < n; ++i)
            deltas[i] = sums[i] - sums[i - 1];

        sums_ = make_unique<sum_segment_tree>(deltas);
    }

    ll find_sum(int node) const
    {
        const int pos = index_[node];
        return sums_->find_sum(0, pos);
    }

    void assign(int node, ll val)
    {
        const ll delta = val - values_[node];
        values_[node] = val;
        int pos = index_[node];
        sums_->add(pos, delta);
        size_t end = pos + subtree_[pos] - 1;
        if (end + 1 < index_.size())
            sums_->add(end + 1, -delta);
    }

private:
    int dfs(const tree& t, const vector<ll>& values, int x, int p,
            ll sum, vector<ll>& sums)
    {
        int pos = order_.size();
        index_[x] = pos;
        order_.push_back(x);
        subtree_.push_back(1);
        sums.push_back(sum + values[x]);

        for (int child: t[x]) {
            if (child == p)
                continue;
            subtree_[pos] += dfs(t, values, child, x, sum + values[x], sums);
        }

        return subtree_[pos];
    }

private:
    vector<int> index_;
    vector<ll> values_;
    vector<int> order_;
    vector<int> subtree_;
    unique_ptr<sum_segment_tree> sums_;
};

enum Query {
    ASSIGN = 1,
    SUM = 2
};

int main()
{
    int n, q;
    cin >> n >> q;

    vector<ll> values(n);
    for (int i = 0; i < n; ++i)
        cin >> values[i];   

    tree t(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        t[a].push_back(b);
        t[b].push_back(a);
    }

    path p(t, values);

    while (q--) {
        int qt = 0;
        cin >> qt;
        if (qt == Query::ASSIGN) {
            int node, val;
            cin >> node >> val;
            --node;
            p.assign(node, val);
        } else if (qt == Query::SUM) {
            int node;
            cin >> node;
            --node;
            cout << p.find_sum(node) << '\n';
        }
    }

    return 0;
}
