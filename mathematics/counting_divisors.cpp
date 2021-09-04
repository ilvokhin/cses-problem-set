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

int count_divisors(int x)
{
    int divisors = 0;

    for (int i = 1; 1LL * i * i <= x; ++i) {
        if (x % i)
            continue;
        int a = i;
        int b = x / i;
        divisors += 1 + (a != b);
    }

    return divisors;
}

int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    while (n--) {
        int x;
        cin >> x;
        cout << count_divisors(x) << '\n';
    }

    return 0;
}
