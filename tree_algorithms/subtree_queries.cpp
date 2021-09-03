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
    sum_segment_tree(const vector<int>& v):
        n_(v.size()),
        tree_(4 * n_)
    {
        build(v, 0, 0, n_ - 1);
    }

    ll find_sum(int l, int r) const
    {
        return find_sum(0, 0, n_ - 1, l, r);
    }

    void assign(int pos, ll val)
    {
        assign(0, 0, n_ - 1, pos, val);
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

    void assign(int x, int tree_l, int tree_r, int pos, ll val)
    {
        if (tree_l == tree_r) {
            tree_[x] = val;
            return;
        }

        int m = (tree_l + tree_r) / 2;
        if (pos <= m)
            assign(2 * x + 1, tree_l, m, pos, val);
        else
            assign(2 * x + 2, m + 1, tree_r, pos, val);

        tree_[x] = tree_[2 * x + 1] + tree_[2 * x + 2];
    }

private:
    int n_;
    vector<ll> tree_;
};

class sum_subtree {
public:
    sum_subtree(const tree& t, vector<int>& values):
        index_(t.size())
    {
        vector<int> ordered_values;
        dfs(t, values, 0, -1, ordered_values);
        values_ = make_unique<sum_segment_tree>(ordered_values);
    }

    void assign(int node, ll val)
    {
        int pos = index_[node];
        values_->assign(pos, val);
    }

    ll find_sum(int node) const
    {
        int pos = index_[node];
        return values_->find_sum(pos, pos + subtree_[pos] - 1);
    }

private:
    int dfs(const tree& t, const vector<int>& values, int x, int p,
            vector<int>& ordered_values)
    {
        const size_t pos = order_.size();
        index_[x] = pos;
        order_.push_back(x);
        subtree_.push_back(1);
        ordered_values.push_back(values[x]);

        for (int child: t[x]) {
            if (child == p)
                continue;
            subtree_[pos] += dfs(t, values, child, x, ordered_values);
        }

        return subtree_[pos];
    }

private:
    vector<int> index_;
    vector<int> order_;
    vector<int> subtree_;
    std::unique_ptr<sum_segment_tree> values_;
};

enum Query {
    ASSIGN = 1,
    SUM = 2
};

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> values(n);
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

    sum_subtree s(t, values);

    while (q--) {
        int qt = 0;
        cin >> qt;
        if (qt == Query::ASSIGN) {
            int node, x;
            cin >> node >> x;
            --node;
            s.assign(node, x);
        } else if (qt == Query::SUM) {
            int node;
            cin >> node;
            --node;
            cout << s.find_sum(node) << '\n';
        }
    }

    return 0;
}
