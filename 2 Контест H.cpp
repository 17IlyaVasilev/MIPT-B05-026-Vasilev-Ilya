#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void LSD(vector<long long>& a1) {

	long long b = 1;
	vector<long long> a;
	vector < pair<long long, long long >> tm0;
	vector < pair<long long, long long >> tm1;

	for (int i = 0; i < a1.size(); ++i) {

		tm0.push_back({ a1[i],i });

	}

	while (b <= 64) {

		vector < pair<long long, long long >> tmx0;
		vector < pair<long long, long long >> tmx1;

		for (auto i : tm0) {

			if (i.first % 2 == 0) {

				tmx0.push_back({ i.first / 2,i.second });

			}
			else {

				tmx1.push_back({ i.first / 2,i.second });

			}

		}

		for (auto i : tm1) {

			if (i.first % 2 == 0) {

				tmx0.push_back({ i.first / 2,i.second });

			}
			else {

				tmx1.push_back({ i.first / 2,i.second });

			}

		}

		tm0.clear();
		tm1.clear();

		for (auto i : tmx0) {

			tm0.push_back(i);

		}

		for (auto i : tmx1) {

			tm1.push_back(i);

		}

		b++;

	}
	for (auto i : tm0) {

		a.push_back(a1[i.second]);

	}

	for (auto i : tm1) {

		a.push_back(a1[i.second]);

	}

	for (int i = 0; i < a.size(); i++) {

		a1[i] = a[i];

	}

}




int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	vector<long long> a;
	int n;
	long long c;
	cin >> n;

	for (int i = 0; i < n; ++i) {

		cin >> c;
		a.push_back(c);
	}

	LSD(a);

	for (auto i : a) {

		cout << i << ' ';

	}

	return 0;

}
