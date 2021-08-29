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

int get_gray_code(int n)
{
    return n ^ (n >> 1);
}

string make_bin(int x, int len)
{
    string bin(len, '0');

    for (int i = 0; i < len; ++i)
        if ((x >> i) & 1)
            bin[i] = '1';

    reverse(bin.begin(), bin.end());
    return bin;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < (1 << n); ++i)
        cout << make_bin(get_gray_code(i), n) << '\n';

    return 0;
}
