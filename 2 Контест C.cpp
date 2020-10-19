#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int KTH(int* a, int n, int k)
{
	int l = 0, r = n - 1;
	while (true)
	{
		if (r <= l + 1)
		{
			if (a[r] < a[l]) swap(a[l], a[r]);
			return a[k];
		}
		swap(a[(l + r) / 2], a[l + 1]);
		if (a[l] > a[r]) swap(a[l], a[r]);
		if (a[l + 1] > a[r]) swap(a[l + 1], a[r]);
		if (a[l] > a[l + 1]) swap(a[l], a[l + 1]);
		int i = l + 1, j = r, cur = a[i];
		while (true) {
			while (a[++i] < cur);
			while (a[--j] > cur);
			if (i > j) break;
			swap(a[i], a[j]);
		}
		a[l + 1] = a[j];
		a[j] = cur;
		if (j >= k) r = j - 1;
		if (j <= k) l = i;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, k;
	cin >> n >> k;
	int* a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << KTH(a, n, k);
	delete[] a;
}