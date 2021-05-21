#include <iostream>
#include <algorithm>
#include <vector>
#include <set>


using namespace std;


class Graph {
private:
	size_t count_vert = 0;
	vector<pair<int, pair<int, int>>> list;
	vector<int> parent;

public:
	Graph() = default;

	Graph(const int& n) {
		count_vert = n;

		for (int i = 0; i <= n; ++i) {
			parent.push_back(i);
		}
	}

	~Graph() {}

	void insert_e(const int& a, const int& b, const int& c) {
		list.push_back({ c, {a,b} });
	}

	long long check_parents(const long long& v) {
		if (v == parent[v]) {

			return parent[v];
		}

		return parent[v] = check_parents(parent[v]);
	}

	void make_sorted() {
		sort(list.begin(), list.end());
	}

	vector<pair<int, pair<int, int>>> get_list() const {

		return list;
	}

	size_t get_count_vert() const {

		return count_vert;
	}

	long long solve() {
		vector<int> sz(get_count_vert() + 1, 1);
		long long ans = 0;

		for (auto e : list) {
			if (check_parents(e.second.first) != check_parents(e.second.second)) {
				ans += e.first;
				auto a = check_parents(e.second.first);
				auto b = check_parents(e.second.second);
				if (sz[a] < sz[b]) {
					swap(a, b);
				}

				parent[b] = a;
				sz[a] += sz[b];
			}
		}

		return ans;
	}
};


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;

	Graph graph(n);
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		graph.insert_e(a, b, c);
	}

	graph.make_sorted();

	cout << graph.solve();

	return 0;
}