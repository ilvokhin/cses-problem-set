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

class dsu {
	vector<int> parent;
	vector<int> rank;
    vector<int> elems;
    int components;
    int largest;
public:
	dsu(const int size):
        parent(size),
        rank(size),
        elems(size),
        components(size),
        largest(0)
    {
        for (int i = 0; i < size; i++)
            make_set(i);
    }

	void make_set(int v)
	{
		parent[v] = v;
		rank[v] = 0;
        elems[v] = 1;
	}

	int find_set(int v)
	{
		if (parent[v] != v)
			parent[v] = find_set(parent[v]);
		return parent[v];
	}

	bool union_set(int v, int u)
	{
		int a = find_set(v), b = find_set(u);
		if (a != b) {
			if (rank[a] > rank[b]) {
				parent[b] = a;
                elems[a] += elems[b];

                if (elems[a] > elems[largest])
                    largest = a;
			} else {
				parent[a] = b;
				if (rank[a] == rank[b])
                    rank[b]++;
                elems[b] += elems[a];
                if (elems[b] > elems[largest])
                    largest = b; 
			}
            --components;
            return true;
		}

        return false;
	}

    int get_components() const
    {
        return components;
    }

    int get_largest_size() const
    {
        return elems[largest];
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    dsu d(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        d.union_set(a, b);
        cout << d.get_components() << " " << d.get_largest_size() << '\n';
    }

    return 0;
}
