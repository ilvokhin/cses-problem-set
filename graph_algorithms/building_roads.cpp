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

class dsu
{
	vector<int> parent;
	vector<int> rank;
public:
	dsu(const int size): parent(size), rank(size)
    {
        for (int i = 0; i < size; i++)
            make_set(i);
    }

	void make_set(int v)
	{
		parent[v] = v;
		rank[v] = 0;
	}

	int find_set(int v)
	{
		if (parent[v] != v)
			parent[v] = find_set(parent[v]);
		return parent[v];
	}

	void union_set(int v, int u)
	{
		int a = find_set(v), b = find_set(u);
		if (a != b)
		{
			if (rank[a] > rank[b])
				parent[b] = a;
			else
			{
				parent[a] = b;
				if (rank[a] == rank[b])
                    rank[b]++;
			}
		}
	}
};

int main()
{
    int n, m;
    cin >> n >> m;

    dsu d(n);

    for (int i = 0; i < m; ++i) {
        int a = 0, b = 0;
        cin >> a >> b;
        --a, --b;

        d.union_set(a, b);
    }

    vector<pair<int, int>> to_add;
    for (int i = 1; i < n; ++i) {
        if (d.find_set(i) == d.find_set(0))
            continue;

        d.union_set(0, i);
        to_add.push_back({ 1, i + 1});
    }

    cout << to_add.size() << endl;
    for (const auto& e: to_add)
        cout << e.first << ' ' << e.second << '\n';

    return 0;
}
