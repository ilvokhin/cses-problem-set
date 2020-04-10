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
    ll n;
    cin >> n;

    ll p = 5;
    ll out = 0;

    while (n / p) {
        out += n / p;
        p *= 5;
    }

    cout << out << endl;

    return 0;
}
