#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

void LSD(string* a, int n, int m) {
	char c;
	for (int i = 0; i < m; i++) {
		vector<int> b[10];
		for (int j = 0; j < n; j++) {
			int d = a[j].length();
			if (d - i - 1 < 0) {
				b[0].push_back(j);
			}
			else {
				c = a[j][a[j].size() - i - 1];
				b[int(c) - 48].push_back(j);
			}
		}
		string* s = new string[n];
		for (int j = 0; j < n; j++) {
			s[j] = a[j];
		}
		int k = 0;
		for (int j = 0; j < 10; j++) {
			for (int l = 0; l < b[j].size(); l++) {
				a[k] = s[b[j][l]];
				k++;
			}
		}
		delete[] s;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m = 0;
	cin >> n;
	string* a = new string[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (m < a[i].size()) m = a[i].size();
	}
	LSD(a, n, m);
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	delete[] a;
	return 0;
}