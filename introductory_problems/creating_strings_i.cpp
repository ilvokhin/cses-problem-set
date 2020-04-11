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

void do_perm(const string& s, string& perm, vector<bool>& used,
             set<string>& out)
{
    if (perm.size() == s.size()) {
        out.insert(perm);
        return;
    }

    int n = s.size();
    for (int i = 0; i < n; ++i) {
        if (used[i])
            continue;

        used[i] = true;
        perm.push_back(s[i]);

        do_perm(s, perm, used, out);

        perm.pop_back();
        used[i] = false;
    }
}

int main()
{
    string s;
    cin >> s;

    set<string> out;
    vector<bool> used(s.size());
    string perm;

    do_perm(s, perm, used, out);

    cout << out.size() << '\n';
    for(const auto& p: out)
        cout << p << '\n';

    return 0;
}
