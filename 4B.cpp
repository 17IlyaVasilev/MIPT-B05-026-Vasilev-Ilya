#include <iostream>
 
using namespace std;
 
class Tree_of_segment_on_sum {
private:
	int tree[400001];
public:
	Tree_of_segment_on_sum();
	~Tree_of_segment_on_sum();
	void build_tree(int [], int, int, int);
	int sum_of_tree(int, int, int, int, int);
	void update_tree(int, int, int, int, int);
 
};
 
Tree_of_segment_on_sum::Tree_of_segment_on_sum() {
 
}
Tree_of_segment_on_sum::~Tree_of_segment_on_sum() {
 
}
void Tree_of_segment_on_sum::build_tree(int a[], int v, int left, int right) {
	if (left == right) {
		if (left % 2 == 1) tree[v] = a[left]; else tree[v] = -a[left];
	}
	else {
		build_tree(a, v * 2, left, (left + right) / 2);
		build_tree(a, v * 2 + 1, (left + right) / 2 + 1, right);
		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}
}
int Tree_of_segment_on_sum::sum_of_tree(int v, int left, int right, int l, int r) {
	if (l > r) return 0;
	if (l == left && r == right) return tree[v];
	return sum_of_tree(v * 2, left, (left + right) / 2, l, min(r, (left + right) / 2)) + sum_of_tree(v * 2 + 1, (left + right) / 2 + 1, right, max(l, (left + right) / 2 + 1), r);
}
 
void Tree_of_segment_on_sum::update_tree(int v, int left, int right, int ind, int change) {
	if (left == right) tree[v] = change;
	else {
		if (ind <= (left + right) / 2) update_tree(v * 2, left, (left + right) / 2, ind, change);
		else update_tree(v * 2 + 1, (left + right) / 2 + 1, right, ind, change);
		tree[v] = tree[v * 2] + tree[v * 2 + 1];
	}
}
 
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
 
	Tree_of_segment_on_sum tr;
	int n, k, c;
	cin >> n;
	int vv[100001];
	for (int i = 1; i <= n; ++i) cin >> vv[i];
	tr.build_tree(vv, 1, 1, n);
	int x, y, z;
	cin >> k;
	for (int i = 0; i < k; ++i) {
		cin >> x >> y >> z;
		if (x == 1) {
			if (y % 2 == 1) cout << tr.sum_of_tree(1, 1, n, y, z) << '\n';
			else cout << -tr.sum_of_tree(1, 1, n, y, z) << '\n';
		}
		else {
			if (y % 2 == 1) tr.update_tree(1, 1, n, y, z);
			else tr.update_tree(1, 1, n, y, -z);
		}
	}
	return 0;
}
