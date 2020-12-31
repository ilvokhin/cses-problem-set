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

class fenwick_tree {
public:
    fenwick_tree(int n):
        tree_(n)
    {
    }

    fenwick_tree(const vector<int>& v):
        fenwick_tree(v.size())
    {
        for (size_t i = 0; i < v.size(); ++i)
            add(i, v[i]);
    }

    ll sum(int r) const
    {
        ll out = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            out += tree_[r];

        return out;
    }

    ll sum(int l, int r) const
    {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int val)
    {
        int n = tree_.size();

        for (; idx < n; idx = idx | (idx + 1))
            tree_[idx] += val;
    }

private:
    vector<ll> tree_;
};

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    fenwick_tree tree(v);

    for (int query = 0; query < q; ++query) {
        int t;
        cin >> t;
        if (t == 1) {
            int k, next_val;
            cin >> k >> next_val;
            --k;
            int prev = v[k];
            v[k] = next_val;
            tree.add(k, next_val - prev);
        } else {
            int a, b;
            cin >> a >> b;
            --a, --b;
            cout << tree.sum(a, b) << endl;
        }
    }

    return 0;
}
