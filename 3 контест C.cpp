#include <iostream>

using namespace std;

struct Node {
	int x;
	int y;
	int size;
	Node* l;
	Node* r;

	Node(int nx) {
		x = nx;
		y = rand();
		l = nullptr;
		r = nullptr;
		size = 1;
	}
};

class Struct_in_out_kth {
public:
	void insert(Node*&, Node*);
	void erase(Node*&, int);
	int find_max_kth(Node*&, int);

private:
	void split(Node*, Node*&, Node*&, int);
	void merge(Node*&, Node*, Node*);
	int size(Node*& root) {
		return root != nullptr ? root->size : 0;
	}
	void updateSize(Node*& root) {
		if (root != nullptr) root->size = 1 + size(root->l) + size(root->r);
	}
};

void Struct_in_out_kth::split(Node* root, Node*& l, Node*& r, int x) {
	if (root == nullptr) {
		l = nullptr;
		r = nullptr;
	} else if (root->x > x) {
		split(root->l, l, root->l, x);
		r = root;
	} else {
		split(root->r, root->r, r, x);
		l = root;
	}

	updateSize(root);
};

void Struct_in_out_kth::merge(Node*& root, Node* l, Node* r) {
	if (l == nullptr || r == nullptr) {
		root = r ? r : l;
	} else if (l->y > r->y) {
		merge(l->r, l->r, r);
		root = l;
	} else {
		merge(r->l, l, r->l);
		root = r;
	}

	updateSize(root);
}

void Struct_in_out_kth::insert(Node*& root, Node* nd) {
	if (root == nullptr) {
		root = nd;
	}
	else if (root->y < nd->y) {
		split(root, nd->l, nd->r, nd->x);
      	root = nd;
	} else {
		insert(nd->x < root->x ? root->l : root->r, nd);
	}

	updateSize(root);
}

void Struct_in_out_kth::erase(Node*& root, int x) {
	if (root->x == x) {
		merge(root, root->l, root->r);
	} else {
		erase(x < root->x ? root->l : root->r, x);
	}

	updateSize(root);
}

int Struct_in_out_kth::find_max_kth(Node*& root, int k) {
	int leftsize = size(root->l);

	if (leftsize == k) {

		return root->x;
	} else if (leftsize > k) {

		return find_max_kth(root->l, k);
	} else {
		k -= leftsize + 1;

		return find_max_kth(root->r, k);
	}
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int s, x, k, n, sz = 0;
	Node* root = nullptr;
	Struct_in_out_kth struct_in_out_kth;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> s;

		if (s == 1) {
			cin >> x;

			Node* newnode = new Node(x);
			struct_in_out_kth.insert(root, newnode);
			sz++;
		}
		else if (s == 0) {
			cin >> k;

			cout << struct_in_out_kth.find_max_kth(root, sz - k);
			cout << endl;
		}
		else {
			cin >> x;

			struct_in_out_kth.erase(root, x);
			sz--;
		}
	}

	return 0;
}