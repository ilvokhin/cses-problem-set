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

class max_segment_tree {
public:
    max_segment_tree(const vector<int>& v):
        n_(v.size()),
        tree_(4 * n_)
    {
        build(v, 0, 0, n_ - 1);
    }

    int find_max(int l, int r) const
    {
        return find_max(0, 0, n_ - 1, l, r);
    }

    void update(int pos, int val)
    {
        update(0, 0, n_ - 1, pos, val);
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

        tree_[x] = max(tree_[2 * x + 1], tree_[2 * x + 2]);
    }

    int find_max(int x, int tree_l, int tree_r, int l, int r) const
    {
        if (l > r)
            return 0;

        if (tree_l == l && tree_r == r)
            return tree_[x];

        int m = (tree_l + tree_r) / 2;

        int a = find_max(2 * x + 1, tree_l, m, l, min(r, m));
        int b = find_max(2 * x + 2, m + 1, tree_r, max(m + 1, l), r);

        return max(a, b);
    }

    void update(int x, int l, int r, int pos, int val)
    {
        // TODO
        if (l == r) {
            tree_[x] = val;
            return;
        }

        int m = (l + r) / 2;
        if (pos <= m)
            update(2 * x + 1, l, m, pos, val);
        else
            update(2 * x + 2, m + 1, r, pos, val);

        tree_[x] = max(tree_[2 * x + 1], tree_[2 * x + 2]);
    }

private:
    int n_;
    vector<int> tree_;
};

int find_room(const max_segment_tree& tree, int target, int n)
{
    int l = 0;
    int r = n - 1;

    while (l < r) {
        int m = l + (r - l) / 2;
        if (tree.find_max(0, m) >= target)
            r = m;
        else
            l = m + 1;
    }

    if (tree.find_max(0, l) >= target)
        return l;

    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> hotels(n);
    for (int i = 0; i < n; ++i)
        cin >> hotels[i];

    vector<int> req(m);
    for (int i = 0; i < m; ++i)
        cin >> req[i];

    vector<int> out;
    out.reserve(m);

    max_segment_tree tree(hotels);

    for (int i = 0; i < m; ++i) {
        int x = req[i];
        int y = find_room(tree, x, n);

        if (y != -1) {
            hotels[y] -= x;
            tree.update(y, hotels[y]);
        }
        out.push_back(y + 1);
    }

    copy(out.begin(), out.end(), ostream_iterator<int>(cout, " "));
    cout << endl; 

    return 0;
}
