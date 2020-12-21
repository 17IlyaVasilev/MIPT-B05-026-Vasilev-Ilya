#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

class Fenwick_tree {
private:
	long long t[300001];
public:
	Fenwick_tree() {};
	~Fenwick_tree() {};
	void inc(const long long&, const long long&, const long long&);
	long long sum(const long long&);
};

void Fenwick_tree::inc(const long long& ind, const long long& n, const long long& d) {
	for (long long i = ind; i < n; i = (i | (i + 1))) t[i] += d;
}

long long Fenwick_tree::sum(const long long& ind) {
	long long ans = 0;
	for (long long i = ind; i > -1; i = (i & (i + 1)) - 1) ans += t[i];
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long q;
	cin >> q;
	vector <pair<long long, long long>> list_of_requests(q);
	vector <long long> mset(q);
	for (long long i = 0; i < q; ++i) {
		char c;
		long long x;
		cin >> c >> x;
		mset[i] = x;
		if (c == '+') list_of_requests[i] = make_pair(1, x); else list_of_requests[i] = make_pair(0, x);
	}

	sort(mset.begin(), mset.end());
	map <long long, long long> before_i;
	before_i[mset[0]] = 1;
	for (long long i = 1; i < mset.size(); i++) if (mset[i] != mset[i - 1]) before_i[mset[i]] = before_i[mset[i - 1]] + 1;

	Fenwick_tree tree;
	for (auto i : list_of_requests) {
		if (i.first == 1) tree.inc(before_i[i.second], mset.size(), i.second);
		else cout << tree.sum(before_i[i.second]) << endl;
	}

	return 0;
}