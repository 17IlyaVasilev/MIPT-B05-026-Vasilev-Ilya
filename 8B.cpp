#include<iostream>
#include <algorithm>
#include <vector>
#include <string>


using namespace std;


class Graph {
private:
	vector<vector<int>> list;

public:
	Graph() = default;

	Graph(const int& n) {
		list.assign(n + 1, vector<int>(0));
	}

	~Graph() {}

	void insert(const int& a, const int& b) {
		list[a].push_back(b);
	}

	vector<vector<int>> get() {

		return list;
	}


};

void dfs(const int& v, vector<vector<int>>& list, vector<int>& used, vector<int>& d, vector<int>& f, long long& timer) {
	used[v] = 1; d[v] = timer++;
	for (int i = 0; i < list[v].size(); ++i)
		if (!used[list[v][i]]) dfs(list[v][i], list, used, d, f, timer);
	f[v] = timer++;
}


pair<vector<int>, vector<int>> pre_cal(const int& n, int& root, Graph& graph) {
	vector<vector<int>> list = graph.get();
	long long timer = 0;
	vector<int> used(n + 1);
	vector<int> d(n + 1);
	vector<int> f(n + 1);

	dfs(root, list, used, d, f, timer);

	return { d, f };
}


int final_check(const pair<vector<int>, vector<int>>& df, const int& a, const int& b) {
	if ((df.first[a] < df.first[b]) && (df.second[b] < df.second[a])) {

		return 1;
	}
	else {
		return 0;
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;

	int root = 0;
	Graph graph(n);

	for (int i = 1; i <= n; ++i) {
		int a;
		cin >> a;
		if (a == 0) {
			root = i;
		}
		else {
			graph.insert(a, i);
		}
	}

	auto df = pre_cal(n, root, graph);

	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		cout << final_check(df, a, b) << endl;
	}

	return 0;
}