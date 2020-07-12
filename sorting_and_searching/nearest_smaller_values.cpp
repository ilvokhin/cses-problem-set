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

    vector<int> out(n);
    vector<int> indexes;

    for (int i = 0; i < n; ++i) {
        while (!indexes.empty() && v[indexes.back()] >= v[i])
            indexes.pop_back();

        out[i] = indexes.empty() ? 0 : indexes.back() + 1;
        indexes.push_back(i);
    }


    copy(out.begin(), out.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    return 0;
}
