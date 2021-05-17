#include<iostream>
#include <algorithm>
#include <vector>
#include <string>
#include<queue>


using namespace std;


class Graph {
private:
	vector<vector<pair<int, int>>> list;

public:
	Graph() = default;

	Graph(const int& n) {
		list.assign(n + 1, vector<pair<int, int>>(0));
	}

	~Graph() {}

	void insert_v(const int& a, const int& b, const int& c) {
		list[a].push_back({ b, c });
		list[b].push_back({ a, c });
	}

	vector<vector<pair<int, int>>> get_list() {

		return list;
	}
};


int length(const int& n, const int& s, const int& t, Graph& graph) {
	priority_queue<pair<int, int>> dist;
	vector<bool> used(n + 1, false);
	vector<int> d(n + 1, 1000000000);
	dist.push({ 0, s });
	d[s] = 0;
	auto g = graph.get_list();

	while (dist.size() > 0) {
		int vert = dist.top().second;
		int count = -dist.top().first;
		used[vert] = true;
		dist.pop();

		for (auto i_vert : g[vert]) {
			if (!used[i_vert.first] && (count + i_vert.second < d[i_vert.first])) {
				d[i_vert.first] = count + i_vert.second;
				dist.push({ -d[i_vert.first], i_vert.first });
			}
		}
	}

	if (d[t] == 1000000000) {
		return -1;
	}
	else {
		return d[t];
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	int s, t;
	cin >> s >> t;

	Graph graph(n);
	for (size_t i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		graph.insert_v(a, b, c);
	}

	cout << length(n, s, t, graph);

	return 0;
}