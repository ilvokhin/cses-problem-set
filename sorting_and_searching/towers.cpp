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

int main()
{
    int n;
    cin >> n;

    multiset<int> st;

    for (int i = 0; i < n; ++i) {
        int x = 0;
        cin >> x;

        auto it = st.upper_bound(x);
        if (it == st.end()) {
            st.insert(x);
            continue;
        }

        st.erase(it);
        st.insert(x);
    }

    cout << st.size() << endl;

    return 0;
}
