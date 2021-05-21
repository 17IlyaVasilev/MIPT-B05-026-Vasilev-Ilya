#include <iostream>
#include <algorithm>
#include <vector>
#include <set>


using namespace std;


class Graph {
private:
	size_t count_vert = 0;
	vector<vector<pair<int, int>>> list;

public:
	Graph() = default;

	Graph(const int& n) {
		count_vert = n;
		list.assign(n + 1, vector<pair<int, int>>(0));
	}

	~Graph() {}

	void insert_v(const int& a, const int& b, const int& c) {
		list[a].push_back({ c, b });
		list[b].push_back({ c, a });
	}

	void reorganization() {
		for (int i = 1; i <= count_vert; ++i) {
			if (list[i].size() > 0) {
				sort(list[i].begin(), list[i].end());
				reverse(list[i].begin(), list[i].end());
			}
		}
	}

	vector<vector<pair<int, int>>> get_list() const {

		return list;
	}

	size_t get_count_vert() const {

		return count_vert;
	}
};


long long result(const Graph& glob_graph) {
	auto graph = glob_graph.get_list();
	long long ans = 0;
	vector<bool> mst(glob_graph.get_count_vert() + 1, false);
	mst[1] = true;
	set<int> Mst;
	Mst.insert(1);

	for (int i = 1; i < glob_graph.get_count_vert(); ++i) {
		int minn = 1000000;
		int nw = 0;
		for (auto v : Mst) {
			if (graph[v].size() > 0) {
				while (mst[graph[v][graph[v].size() - 1].second]) {
					graph[v].pop_back();
					if (graph[v].size() == 0) break;
				}
				if (graph[v].size() > 0) {
					if (graph[v][graph[v].size() - 1].first < minn) {
						nw = graph[v][graph[v].size() - 1].second;
						minn = graph[v][graph[v].size() - 1].first;
					}
				}
			}
		}
		ans += minn;
		mst[nw] = true;
		Mst.insert(nw);
	}

	return ans;
}


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

		graph.insert_v(a, b, c);
	}

	graph.reorganization();

	cout << result(graph);

	return 0;
}