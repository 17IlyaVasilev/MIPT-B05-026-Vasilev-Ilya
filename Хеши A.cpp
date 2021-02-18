#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Hesh {
private:
	vector<pair<string, long long>> a[100003];
	const long long p = 100003;
	const long long INF = 10000000;
	long long Get_hesh(const string&);

public:
	Hesh() = default;
	~Hesh() {};
	long long Change_var(const string&, const long long&);

};

long long Hesh::Get_hesh(const string& s) {
	long long temp = 1;
	long long h = 0;
	for (long long i = 0; i < min((int)s.length(), 1000); ++i) {
		h += (long long)s[i] * temp;
		h %= p;
		temp *= p;
		temp %= INF;
	}
	return h;
}

long long Hesh::Change_var(const string& s, const long long& b) {
	long long h = Get_hesh(s);
	if (a[h].size() == 0) {
		a[h].push_back({ s, b });
		return b;
	}
	else {
		for (long long i = 0; i < a[h].size(); ++i) {
			if (a[h][i].first == s) {
				a[h][i].second += b;
				return a[h][i].second;
				break;
			}
			else
				if (i + 1 == a[h].size()) {
					a[h].push_back({ s, b });
					return b;
					break;
				}
		}
	}

}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	string s;
	long long b;
	Hesh hesh;

	while (cin >> s) {
		cin >> b;
		cout << hesh.Change_var(s, b) << endl;
	}
	~hesh();
	return 0;
}