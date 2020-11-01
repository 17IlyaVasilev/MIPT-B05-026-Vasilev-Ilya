#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

pair <int, int> partition (vector <int>& a, int l, int r, int mid) {

	swap(a[(l + r) / 2], a[l + 1]);

	if (a[l] > a[r]) {

		swap(a[l], a[r]);

	}

	if (a[l + 1] > a[r]) {

		swap(a[l + 1], a[r]);

	}

	if (a[l] > a[l + 1]) {

		swap(a[l], a[l + 1]);

	}

	int i = l + 1, j = r;

	while (true) {

		while (a[++i] < mid);
		while (a[--j] > mid);

		if (i > j)break;

		swap(a[i], a[j]);

	}

	a[l + 1] = a[j];
	a[j] = mid;

	return { i, j };

}

int kth(vector <int> a, int n, int k){

	int l = 0, r = n - 1;

	while (true)
	{

		if (r <= l + 1)
		{

			if (a[r] < a[l]) {

				swap(a[l], a[r]);

			}

			return a[k];

		}

		auto q = partition(a, l, r, a[l + 1]);

		int i = q.first, j = q.second;

		if (j >= k) {

			r = j - 1;

		}

		if (j <= k) {

			l = i;

		}

	}

}

int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, k, c;

	cin >> n >> k;

	vector<int> b;

	for (int i = 0; i < n; i++) {

		cin >> c;
		b.push_back(c);

	}

	cout << kth(b, n, k);

}
