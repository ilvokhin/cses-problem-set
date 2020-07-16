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

struct elem {
    elem(int value = 0, int idx = 0):
        value(value), idx(idx)
    { }

    int value;
    int idx;
};

bool operator < (const elem& x, const elem& y)
{
    return tie(x.value, x.idx) < tie(y.value, y.idx);
}

bool operator == (const elem& x, const elem& y)
{
    return tie(x.value, x.idx) == tie(y.value, y.idx);
}

ostream& operator << (ostream& os, const elem& e)
{
    os << e.value << " " << e.idx;
    return os;
}

int find_median(const set<elem>& st, const set<elem>::iterator& it)
{
    assert(!st.empty());
    assert(it != st.end());

    return it->value;
}

set<elem>::iterator update(set<elem>& st, set<elem>::iterator it,
                           const elem& out, const elem& in)
{
    if (*it == out) {
        st.insert(in);
        if (*it < in) {
            return st.erase(it);
        }
        else {
            return --st.erase(it);
        }
    }

    if ((out < *it && in < *it) || (*it < out && *it < in)) {
        st.erase(out);
        st.insert(in);

        return it;
    }

    if (out < *it && *it < in) {
        st.erase(out);
        st.insert(in);

        return ++it;
    }

    st.erase(out);
    st.insert(in);
    return --it;
}

set<elem>::iterator get_median_iter(const set<elem>& st, int k)
{
    auto it = st.begin();
    advance(it, k / 2);

    if (st.size() % 2 == 0)
        --it;

    return it;
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    set<elem> st;

    for (int i = 0; i < k; ++i)
        st.emplace(v[i], i);

    auto it = get_median_iter(st, k);

    for (int i = k; i < n; ++i) {
        cout << find_median(st, it) << " ";

        elem out(v[i - k], i - k);
        elem in(v[i], i);

        it = update(st, it, out, in);
    }
    cout << find_median(st, it) << endl;

    return 0;
}
