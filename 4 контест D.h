#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

long long t[300001];

void inc(long long ind, long long n) {
	for (long long i = ind; i < n; i = (i | (i + 1))) t[i]++;
}

void sum(long long ind, long long& ans) {
	for (long long i = ind; i > -1; i = (i & (i + 1)) - 1) ans += t[i];
}

bool cmp(pair <long long, long long> l, pair <long long, long long> r) {
	if (l.first != r.first) return l.first > r.first;
	return l.second < r.second;
}

long long sum_1_n(long long n) {
	return ((n - 1) * n) / 2;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	for (long long i = 0; i <= 300000; ++i) t[i] = 0;
	vector <pair <long long, long long>> l_r;
	vector <pair <long long, long long>> r_ind;
	long long n;
	cin >> n;
	for (long long i = 0; i < n; ++i) {
		long long ll, rr;
		cin >> ll >> rr;
		l_r.push_back(make_pair(ll, rr));
	}

	sort(l_r.begin(), l_r.end(), cmp);
	long long ans = 0;
	long long same = 1;
	for (long long i = 1; i < n; ++i) {
		if (l_r[i] == l_r[i - 1])same++;
		else {
			ans -= sum_1_n(same);
			same = 1;
		}
	}
	if (same > 1) ans -= sum_1_n(same);

	for (long long i = 0; i < n; ++i) r_ind.push_back(make_pair(l_r[i].second, i));
	sort(r_ind.begin(), r_ind.end());
	for (long long i = 0; i < n; ++i) {
		inc(r_ind[i].second, n);
		sum(r_ind[i].second - 1, ans);
	}
	cout << ans;
	return 0;
}