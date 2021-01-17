#include <algorithm>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <utility>
#include <string>
#include <vector>
#include <limits>
#include <queue>
#include <cmath>
#include <map>
#include <set>

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

const int INF = numeric_limits<int>::max();
using ll = long long;
using key = pair<int, int>;
using ordered_tree = tree<key,
                          null_type,
                          less<key>,
                          rb_tree_tag,
                          tree_order_statistics_node_update>;

int main()
{
    ios::sync_with_stdio(false);

    int n, q;
    cin >> n >> q;

    ordered_tree t;
    vector<int> employees(n);
    for (int i = 0; i < n; ++i) {
        cin >> employees[i];
        t.insert(make_pair(employees[i], i));
    }

    for (int query = 0; query < q; ++query) {
        char op;
        cin >> op;
        if (op == '!') {
            int k, x;
            cin >> k >> x;
            --k;

            t.erase(make_pair(employees[k], k));
            employees[k] = x;
            t.insert(make_pair(employees[k], k));
        } else {
            int a, b;
            cin >> a >> b;

            int x = t.order_of_key(make_pair(a - 1, INF));
            int y = t.order_of_key(make_pair(b, INF));

            cout << y - x << '\n';
        }
    }

    return 0;
}
