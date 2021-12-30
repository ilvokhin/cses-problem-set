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
    int t;
    cin >> t;

    while (t--) {
        int n, s = 0;
        cin >> n;;
        for (int i = 0; i < n; ++i) {
            int x = 0;
            cin >> x;
            s ^= x;
        }

        cout << (s == 0 ? "second" : "first") << endl;
    }

    return 0;
}
