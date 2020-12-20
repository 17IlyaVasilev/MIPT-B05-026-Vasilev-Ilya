#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const long long INF = 1000000001;

class Sparse_Table {
private:
	vector<vector<pair<long long, long long>>> st;
	vector<long long> degree;
public:
	Sparse_Table(const vector<long long>&);
	long long sth(long long, long long);
};
Sparse_Table::Sparse_Table(const vector<long long>& v) {
	vector<pair<long long, long long>> temp;
	temp.push_back({ INF,INF });
	for (size_t i = 1; i < v.size(); ++i) temp.push_back({ v[i],INF });
	st.push_back(temp);
	long long k = 1;
	long long s = 2;
	vector<pair<long long, long long>> c;
	while (v.size() - s + 1 > 0) {
		st.push_back(c);
		st[k].push_back(make_pair(0, 0));
		for (long long i = 1; i <= v.size() - s; ++i) {
			st[k].push_back(make_pair(min(st[k - 1][i].first, st[k - 1][i + s / 2].first), min(max(st[k - 1][i].first, st[k - 1][i + s / 2].first), min(st[k - 1][i].second, st[k - 1][i + s / 2].second))));
		}
		++k;
		s *= 2;
	}
	degree.push_back(1);
	for (long long i = 1; i < st.size(); ++i) degree.push_back(degree[i - 1] * 2);
}

long long Sparse_Table::sth(long long l, long long r) {
	long long k = log2(r - l + 1);
	long long s = degree[k];
	if (st[k][l].first == st[k][r - s + 1].first) return min(st[k][l].second, st[k][r - s + 1].second);
	else return min(max(st[k][l].first, st[k][r - s + 1].first), min(st[k][l].second, st[k][r - s + 1].second));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long n, x, m;
	cin >> n >> m;
	vector<long long> v(n + 1);
	for (long long i = 1; i <= n; ++i) {
		cin >> x;
		v[i] = x;
	}
	Sparse_Table ST(v);
	long long l, r;
	for (long long i = 0; i < m; ++i) {
		cin >> l >> r;
		cout << ST.sth(l, r) << endl;
	}
	return 0;
}
