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

void do_fill(char ch, int cnt, string& dst, int& pos)
{
    int n = dst.size();

    while (cnt) {
        assert(cnt >= 2);

        int x = pos;
        int y = n - pos - 1;

        dst[x] = dst[y] = ch;

        ++pos;
        cnt -= 2;
    }
}

int main()
{
    string s;
    cin >> s;

    map<char, int> cnt;

    for (char ch: s)
        ++cnt[ch];

    ll odd_cnt = 0;
    auto last_it = cnt.end();
    for (auto kv = cnt.begin(); kv != cnt.end(); ++kv) {
        if (kv->second % 2 == 0)
            continue;

        ++odd_cnt;
        last_it = kv;
    }

    if (odd_cnt > 1) {
        cout << "NO SOLUTION\n";
        return 0;
    }

    string out(s.size(), '?');
    if (last_it != cnt.end()) {
        out[s.size() / 2] = last_it->first;
        --(last_it->second);
        if (last_it->second == 0)
            cnt.erase(last_it);
    }

    int cur = 0;
    for (const auto& kv: cnt)
        do_fill(kv.first, kv.second, out, cur);

    cout << out << endl;

    return 0;
}
