#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void LSD(vector<long long> a) {

	long long c = 0, d = 0;
	vector <long long> a1;
	vector<int> b[256];

	for (int j = 0; j < 8; ++j) {

		for (int i = 0; i < a.size(); ++i) {

			d = (a[i] >> (8 * j)) & 255;
			b[d].push_back(i);

		}

		for (int i = 0; i < 256; ++i) {

			for (int l = 0; l < b[i].size(); ++l) {

				a1.push_back(a[b[i][l]]);

			}

			b[i].clear();

		}

		for (int i = 0; i < a1.size(); ++i) {

			a[i] = a1[i];

		}

		a1.clear();

	}

	for (int i = 0; i < a.size(); ++i) {

		cout << a[i] << ' ';

	}

}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	long long m;
	vector<long long> a;

	cin >> n;

	for (int i = 0; i < n; ++i) {

		cin >> m;
		a.push_back(m);

	}

	LSD(a);

	return 0;

}
