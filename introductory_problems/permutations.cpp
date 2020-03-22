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

bool is_good(const vector<int>& perm)
{
    int n = perm.size();
    for (int i = 1; i < n; ++i)
        if(abs(perm[i - 1] - perm[i]) <= 1)
            return false;

    return true;
}

int main()
{
    int n;
    cin >> n;

    vector<int> out;
    out.reserve(n);

    for (int i = 1; i < n; i += 2)
        out.push_back(i + 1);

    for (int i = 0; i < n; i += 2)
        out.push_back(i + 1);

    if (is_good(out)) {
        copy(out.begin(), out.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
        return 0;
    }

    cout << "NO SOLUTION" << endl;

    return 0;
}
