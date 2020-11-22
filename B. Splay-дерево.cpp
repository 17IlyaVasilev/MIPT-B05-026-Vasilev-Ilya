#include <iostream>
#include <algorithm>

using namespace std;

const long long MIN = -1'000'000'001;
const long long MAX = 1'000'000'001;

struct node {

	node* left;
	node* right;
	long long key;
	long long sum;
	long long min, max;
	long long height;

	node(long long k) {

		left = nullptr;
		right = nullptr;
		key = k;
		min = k;
		max = k;
		sum = 0;
		height = 1;

	}

};

class Splay_tree {

public:

	long long sum(node*&, long long, long long);
	void insert_node(node*&, long long);

private:

	long long get_height_left(node*&);
	long long get_height_right(node*&);
	long long get_balance(node*&);
	long long get_sum_left(node*&);
	long long get_sum_right(node*&);
	long long get_min_left(node*&);
	long long get_min_right(node*&);
	long long get_max_left(node*&);
	long long get_max_right(node*&);
	void recalc_min_max(node*&);
	void recalc_sum(node*&);
	void recalc(node*&);
	node* find(node*&, int);
	bool exists(node*&, long long);
	node* right_rotate(node*&);
	node* left_rotate(node*&);
	node* rebalance(node*&);
	node* insert(node*&, long long);

};

long long Splay_tree::get_height_left(node*& p) {

	if (p->left == nullptr) {

		return 0;

	}

	return p->left->height;

}

long long Splay_tree::get_height_right(node*& p) {

	if (p->right == nullptr) {

		return 0;

	}

	return p->right->height;

}
long long Splay_tree::get_balance(node*& p) {

	return get_height_right(p) - get_height_left(p);

}

long long Splay_tree::get_sum_left(node*& p) {

	if (p->left) {

		return p->left->sum;

	}

	return 0;

}

long long Splay_tree::get_sum_right(node*& p) {

	if (p->right) {

		return p->right->sum;

	}

	return 0;

}

long long Splay_tree::get_min_left(node*& p) {

	if (p->left) {

		return p->left->min;

	}

	return MAX;

}

long long Splay_tree::get_min_right(node*& p) {

	if (p->right) {

		return p->right->min;

	}

	return MAX;

}

long long Splay_tree::get_max_left(node*& p) {

	if (p->left) {

		return p->left->max;

	}

	return MIN;

}

long long Splay_tree::get_max_right(node*& p) {

	if (p->right) {

		return p->right->max;

	}

	return MIN;

}

void Splay_tree::recalc_min_max(node*& p) {

	p->min = min(min(get_min_left(p), get_min_right(p)), p->key);
	p->max = max(max(get_max_left(p), get_max_right(p)), p->key);

}

void Splay_tree::recalc_sum(node*& p) {

	p->sum = get_sum_left(p) + get_sum_right(p);
	if (p->left) {

		p->sum += p->left->key;

	}

	if (p->right) {

		p->sum += p->right->key;

	}

}

void Splay_tree::recalc(node*& p) {

	p->height = 1 + max(get_height_left(p), get_height_right(p));

}

node* Splay_tree::find(node*& cur_node, int val) {

	if (cur_node == nullptr || cur_node->key == val) {

		return cur_node;

	}

	if (cur_node->key < val) {

		return find(cur_node->right, val);

	}

	return find(cur_node->left, val);

}

bool Splay_tree::exists(node*& cur_node, long long val) {

	return find(cur_node, val) != nullptr;

}

node* Splay_tree::right_rotate(node*& cur_node) {

	node* left = cur_node->left;
	cur_node->left = left->right;
	left->right = cur_node;
	recalc(cur_node);
	recalc_sum(cur_node);
	recalc_min_max(cur_node);
	recalc(left);
	recalc_sum(left);
	recalc_min_max(left);

	return left;

}

node* Splay_tree::left_rotate(node*& cur_node) {

	node* right = cur_node->right;
	cur_node->right = right->left;
	right->left = cur_node;
	recalc(cur_node);
	recalc_sum(cur_node);
	recalc_min_max(cur_node);
	recalc(right);
	recalc_sum(right);
	recalc_min_max(right);

	return right;

}

node* Splay_tree::rebalance(node*& cur_node) {

	if (get_balance(cur_node) == 2) {

		if (get_balance(cur_node->right) < 0) {

			cur_node->right = right_rotate(cur_node->right);

		}

		return left_rotate(cur_node);

	}

	if (get_balance(cur_node) == -2) {

		if (get_balance(cur_node->left) > 0) {

			cur_node->left = left_rotate(cur_node->left);

		}

		return right_rotate(cur_node);

	}

	return cur_node;

}

node* Splay_tree::insert(node*& cur_node, long long new_key) {

	if (cur_node == nullptr) {

		return new node(new_key);

	}

	if (new_key < cur_node->key) {

		cur_node->left = insert(cur_node->left, new_key);

	}
	else
	{

		cur_node->right = insert(cur_node->right, new_key);

	}

	recalc(cur_node);
	recalc_sum(cur_node);
	recalc_min_max(cur_node);

	return rebalance(cur_node);

}

void Splay_tree::insert_node(node*& cur_node, long long new_key) {

	if (exists(cur_node, new_key))return;

	cur_node = insert(cur_node, new_key);

}

long long Splay_tree::sum(node*& cur_node, long long l, long long r) {

	if (cur_node == nullptr) {

		return 0;

	}

	if (cur_node->key > r) {

		return sum(cur_node->left, l, r);

	}

	if (cur_node->key < l) {

		return sum(cur_node->right, l, r);

	}

	if (cur_node->left == nullptr && cur_node->right == nullptr) {

		return cur_node->key;

	}

	if (cur_node->min >= l && cur_node->max <= r) {

		return cur_node->sum + cur_node->key;

	}

	return sum(cur_node->left, l, r) + sum(cur_node->right, l, r) + cur_node->key;

}

int main() {

	Splay_tree tree;
	node* root = nullptr;
	char prev = '+';
	long long res = 0, n;
	char c;

	cin >> n;

	for (long long i = 0; i < n; ++i) {

		cin >> c;

		if (c == '+') {

			long long x;
			cin >> x;
			if (prev == '?') {

				tree.insert_node(root, (x + res) % 1000000000);

			}
			else
			{

				tree.insert_node(root, x);

			}

		}
		else
		{

			long long l, r;
			cin >> l >> r;
			res = tree.sum(root, l, r);
			cout << res << endl;

		}

		prev = c;

	}

	return 0;

}