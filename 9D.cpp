#include<iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;


class Graph {
private:
	vector<vector<long long>> list;
	vector<pair<pair<long long, long long>, long long>> edge;

public:
	Graph() = default;

	Graph(const int& n) {
		list.assign(n + 1, vector<long long>(0));
	}

	Graph(const int& n, const int& m) {
		list.assign(n + 1, vector<long long>(0));
		edge.assign(m, { {0, 0}, 0 });
	}

	~Graph() {}

	void insert_v(const int& a, const int& b) {
		list[a].push_back(b);
	}

	void insert_e(const long long& a, const long long& b, const long long& c) {
		edge.push_back({ {a, b}, c });
	}

	vector<vector<long long>> get_list() {

		return list;
	}

	vector<pair<pair<long long, long long>, long long>> get_edge() {

		return edge;
	}
};


void dfs(const long long& i, vector<bool>& used, const long long& n, const vector<vector<long long>>& g) {
	used[i] = true;
	for (auto l : g[i])
		if (!used[l]) dfs(l, used, n, g);
}

pair<vector<char>, vector<long long>> result(const long long& n, const long long& s, Graph& graph, const long long INF) {
	auto e = graph.get_edge();
	auto g = graph.get_list();
	vector<long long> dist(n + 1, INF);
	dist[s] = 0;

	for (long long t = 0; t < n; ++t) {
		vector<long long> dist2(n + 1, INF);
		dist2[s] = 0;
		for (auto i : e) {
			if (dist[i.first.first] < INF)
				dist2[i.first.second] = min(dist2[i.first.second], min(dist[i.first.second], dist[i.first.first] + i.second));
		}
		dist = dist2;
	}

	vector<long long> dist2(n + 1, INF);
	dist2[s] = 0;
	for (auto i : e) {
		if (dist[i.first.first] < INF)
			dist2[i.first.second] = min(dist2[i.first.second], min(dist[i.first.second], dist[i.first.first] + i.second));
	}

	vector<char> ans(n + 1, ' ');
	for (long long i = 1; i <= n; ++i) {
		if (dist2[i] < dist[i]) {
			vector<bool> used(n + 1, false);
			dfs(i, used, n, g);
			for (long long j = 1; j <= n; ++j) {
				if (used[j]) {
					ans[j] = '-';
				}
			}
		}
	}

	return { ans, dist };
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	const long long INF = 1000000000000001;
	long long n, m, s;
	cin >> n >> m >> s;

	Graph graph(n);

	for (long long i = 0; i < m; ++i) {
		long long a, b, c;
		cin >> a >> b >> c;

		graph.insert_v(a, b);
		graph.insert_e(a, b, c);
	}

	auto res = result(n, s, graph, INF);
	for (long long i = 1; i <= n; ++i) {
		if (res.first[i] == '-') {
			cout << '-' << endl;
		}
		else if (res.second[i] == INF) {
			cout << '*' << endl;
		}
		else {
			cout << res.second[i] << endl;
		}
	}

	return 0;
}