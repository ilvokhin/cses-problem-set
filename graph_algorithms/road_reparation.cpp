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

struct edge {
    int from;
    int to;
    ll cost;
};

using graph = vector<vector<edge>>;

void dfs(const graph& g, int x, vector<bool>& used)
{
    used[x] = true;

    for (const auto& e: g[x]) {
        int to = e.to;
        if (used[to])
            continue;

        dfs(g, to, used);
    }
}

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
		if (a != b) {
			if (rank[a] > rank[b])
				parent[b] = a;
			else {
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

    graph g(n);

    vector<edge> edges;

    for (int i = 0; i < m; ++i) {
        edge e;
        cin >> e.from >> e.to >> e.cost;

        --e.from;
        --e.to;

        g[e.from].push_back(e);
        g[e.to].push_back({e.to, e.from, e.cost});
        edges.push_back(e);
    }

    vector<bool> used(n);
    dfs(g, 0, used);

    for(int i = 0; i < n; ++i) {
        if (used[i])
            continue;

        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    sort(edges.begin(), edges.end(), [](const edge& a, const edge& b)
                                     { return a.cost < b.cost; });

    dsu d(n);

    ll out = 0;

    for (const edge& e: edges) {
        int u = d.find_set(e.from);
        int v = d.find_set(e.to);

        if (u == v)
            continue;

        d.union_set(u, v);
        out += e.cost;
    }

    cout << out << endl;

    return 0;
}
