#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Hesh_swap {
private:
	vector<pair<long long, long long>> a[1000019];
	const long long p = 1000019;
	
public:
	Hesh_swap() = default;
	~Hesh_swap() {};
	long long swap(const long long&, const long long&);

};

long long Hesh_swap::swap(const long long& s, const long long& b) {
	long long h1 = s % p;
	long long h2 = b % p;
	long long rn1, rn2;
	if (a[h1].size() == 0) {
		a[h1].push_back({ s, b });
		rn1 = s;
	}
	else
		for (long long i = 0; i < a[h1].size(); ++i) {
			if (a[h1][i].first == s) {
				rn1 = a[h1][i].second;
				break;
			}
			else {
				if (i + 1 == a[h1].size()) {
					a[h1].push_back({ s, b });
					rn1 = s;
					break;
				}
			}
		}

	if (a[h2].size() == 0) {
		a[h2].push_back({ b, rn1 });
		rn2 = b;
	}
	else
		for (long long i = 0; i < a[h2].size(); ++i) {
			if (a[h2][i].first == b) {
				rn2 = a[h2][i].second;
				a[h2][i].second = rn1;
				break;
			}
			else {
				if (i + 1 == a[h2].size()) {
					a[h2].push_back({ b, rn1 });
					rn2 = b;
					break;
				}
			}
		}

	for (long long i = 0; i < a[h1].size(); ++i) {
		if (a[h1][i].first == s) {
			a[h1][i].second = rn2;
			break;
		}
	}

	return abs(rn2 - rn1);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	long long n, a, b;
	cin >> n;
	Hesh_swap t;
	for (long long j = 0; j < n; ++j) {
		cin >> a >> b;
		cout << t.swap(a, b) << endl;
	}
	return 0;
}