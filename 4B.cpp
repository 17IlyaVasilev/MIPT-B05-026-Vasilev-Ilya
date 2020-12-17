#include <iostream>
#include <vector>

using namespace std;

vector <long long> v;
long long treem[400001];
long long treep[400001];
long long a[100001];
long long b[100001];

void build_treem(long long v, long long left, long long right) {
	if (left == right) treem[v] = a[left];
	else {
		build_treem(v * 2, left, (left + right) / 2);
		build_treem(v * 2 + 1, (left + right) / 2 + 1, right);
		treem[v] = (treem[v * 2] + treem[v * 2 + 1]);
	}
}

long long trm(long long v, long long left, long long right, long long l, long long r) {
	if (l > r) return 0;
	if (l == left && r == right) return treem[v];
	return trm(v * 2, left, (left + right) / 2, l, min(r, (left + right) / 2)) + trm(v * 2 + 1, (left + right) / 2 + 1, right, max(l, (left + right) / 2 + 1), r);
}

void update_treem(long long v, long long left, long long right, long long ind, long long change) {
	if (left == right) treem[v] = change;
	else {
		if (ind <= (left + right) / 2) update_treem(v * 2, left, (left + right) / 2, ind, change);
		else update_treem(v * 2 + 1, (left + right) / 2 + 1, right, ind, change);
		treem[v] = (treem[v * 2] + treem[v * 2 + 1]);
	}
}

void build_treep(long long v, long long left, long long right) {
	if (left == right) treep[v] = b[left];
	else {
		build_treep(v * 2, left, (left + right) / 2);
		build_treep(v * 2 + 1, (left + right) / 2 + 1, right);
		treep[v] = (treep[v * 2] + treep[v * 2 + 1]);
	}
}

long long trp(long long v, long long left, long long right, long long l, long long r) {
	if (l > r) return 0;
	if (l == left && r == right) return treep[v];
	return trp(v * 2, left, (left + right) / 2, l, min(r, (left + right) / 2)) + trp(v * 2 + 1, (left + right) / 2 + 1, right, max(l, (left + right) / 2 + 1), r);
}

void update_treep(long long v, long long left, long long right, long long ind, long long change) {
	if (left == right) treep[v] = change;
	else {
		if (ind <= (left + right) / 2) update_treep(v * 2, left, (left + right) / 2, ind, change);
		else update_treep(v * 2 + 1, (left + right) / 2 + 1, right, ind, change);
		treep[v] = (treep[v * 2] + treep[v * 2 + 1]);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long n, k, c;
	cin >> n;
	v.push_back(0);
	for (long long i = 0; i < n; ++i) {
		cin >> c;
		v.push_back(c);
	}
	cin >> k;
	for (long long i = 1; i <= n; ++i) {
		if (i % 2 == 1) {
			a[i] = -v[i];
			b[i] = v[i];
		}
		else {
			a[i] = v[i];
			b[i] = -v[i];
		}
	}
	build_treem(1, 1, n);
	build_treep(1, 1, n);
	long long x = 0, y = 0, z = 0;
	for (long long i = 0; i < k; ++i) {
		cin >> x >> y >> z;
		if (x == 1) {
			if (y % 2 == 1) {
				cout << -trm(1, 1, n, y, z) << endl;
			}
			else {
				cout << -trp(1, 1, n, y, z) << endl;
			}
		}
		else {
			if (y % 2 == 1) {
				update_treem(1, 1, n, y, -z);
				update_treep(1, 1, n, y, z);
			}
			else {
				update_treem(1, 1, n, y, z);
				update_treep(1, 1, n, y, -z);
			}
		}
	}
	return 0;
}