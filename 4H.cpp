#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Sparse_Table {
private:
	vector<vector<pair<long long, long long>>> st;
public:
	Sparse_Table();
	~Sparse_Table();
	Sparse_Table operator =(Sparse_Table) = delete;
	Sparse_Table(vector<pair<long long, long long>>&);
	long long sth(long long, long long);
};
Sparse_Table::Sparse_Table(vector<pair<long long, long long>>& v) {
	st.push_back(v);
	long long k = 1;
	long long s = 2;
	vector<pair<long long,long long>> c;
	while (v.size() - s + 1 > 0) {
		st.push_back(c);
		st[k].push_back(make_pair(0, 0));
		for (long long i = 1; i <= v.size() - s; ++i) {
			st[k].push_back(make_pair(min(st[k - 1][i].first, st[k - 1][i + s / 2].first), min(max(st[k - 1][i].first, st[k - 1][i + s / 2].first), min(st[k - 1][i].second, st[k - 1][i + s / 2].second))));
		}
		++k;
		s *= 2;
	}
}

Sparse_Table::Sparse_Table() {

}

Sparse_Table::~Sparse_Table() {
	st.clear();
}

long long Sparse_Table::sth(long long l, long long r) {
	long long k = 0;
	long long s = 1;
	while (r - l + 1 > s) {
		s *= 2;
		++k;
	}
	if (k > 0) {
		--k;
		s /= 2;
	}
	if (st[k][l].first != st[k][r - s + 1].first || st[k][l].first == st[k][l].second) return min(max(st[k][l].first, st[k][r - s + 1].first), min(st[k][l].second, st[k][r - s + 1].second)); else {
		long long u = st[k][l].first;
		long long j = l + s;
		long long kk = 0;
		long long ss = 1;
		while (r - j + 1 > ss) {
			ss *= 2;
			++kk;
		}
		if (kk > 0) {
			--kk;
			ss /= 2;
		}
		if (min(max(st[kk][j].first, st[kk][r - ss + 1].first), min(st[kk][j].second, st[kk][r - ss + 1].second)) == u) return min(max(st[k][l].first, st[k][r - s + 1].first), min(st[k][l].second, st[k][r - s + 1].second)); else {
			return min(st[k][l].second, st[k][r - s + 1].second);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long n, x, m;
	cin >> n >> m;
	vector<pair<long long, long long>> v(n + 1);
	for (long long i = 1; i <= n; ++i) {
		cin >> x;
		v[i].first = x;
		v[i].second = 1000000001;
	}
	Sparse_Table ST(v);
	long long l, r;
	for (long long i = 0; i < m; ++i) {
		cin >> l >> r;
		cout << ST.sth(l, r) << endl;
	}
	return 0;
}