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

void go(const string& x, const string& A, string& edges,
        unordered_set<string>& used)
{
    for (int k = 0; k < 2; ++k) {
        string next = x + A[k];
        if (used.count(next))
            continue;

        used.insert(next);
        go(next.substr(1), A, edges, used);
        edges.push_back(A[k]);
    }
}

string gen(int n)
{
    const string A = "01";
    string edges;
    unordered_set<string> used;

    string x(n - 1, A[0]);
    go(x, A, edges, used);

    string out;
    for (int i = 0; i < (1 << n); ++i)
        out += edges[i];
    out += x;

    return out;
}

int main()
{
    int n;
    cin >> n;

    cout << gen(n) << endl;

    return 0;
}
