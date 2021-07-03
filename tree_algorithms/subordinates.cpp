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

void count_subordinates(const tree& t, int x, vector<int>& subordinates)
{
    for (int child: t[x]) {
        count_subordinates(t, child, subordinates);
        subordinates[x] += 1 + subordinates[child];
    }
}

int main()
{
    int n;
    cin >> n;

    tree t(n);

    for (int i = 1; i < n; ++i) {
        int x = 0;
        cin >> x;
        --x;
        t[x].push_back(i);
    }

    vector<int> subordinates(n);
    count_subordinates(t, 0, subordinates);

    copy(subordinates.begin(), subordinates.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
