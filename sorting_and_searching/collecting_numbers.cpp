#include <unordered_set>
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

    vector<int> v(n);
    for (int i = 0; i < n; ++i)
        cin >> v[i];

    unordered_set<int> seen;
    int rounds = 0;

    for (int x: v) {
        if (!seen.count(x - 1))
            ++rounds;
        seen.insert(x);
    }

    cout << rounds << endl;

    return 0;
}
