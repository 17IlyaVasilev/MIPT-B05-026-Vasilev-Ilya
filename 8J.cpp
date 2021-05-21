#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>


using namespace std;


void IsEulerCycle(size_t v, map<pair<size_t, size_t>, bool>& edge, vector <set<size_t>>& vert, vector<size_t>& ans) {
	size_t temp = 0;

	while (vert[v].size() > 0) {
		for (auto i : vert[v])
			if (edge[{v, i}] == false) {
				vert[v].erase(i);
				edge[{v, i}] = true;
				temp = i;
				break;
			}
		IsEulerCycle(temp, edge, vert);
	}

	ans.push_back(v);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, a;
	cin >> n >> a;

	map<pair<size_t, size_t>, bool> edge;
	vector<set<size_t>> vert(n + 1);
	vector<size_t> ans;

	for (size_t i = 1; i <= n; ++i) {
		for (size_t j = 1; j <= n; ++j) {
			size_t b;
			cin >> b;
			if (b == 0)
				if (i != j) {
					edge[{i, j}] = false;
					vert[i].insert(j);
				}
		}
	}

	IsEulerCycle(a, edge, vert, ans);
	for (size_t i = ans.size() - 1; i > 0; --i)
		cout << ans[i] << " " << ans[i - 1] << endl;

	return 0;
}