#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

class Goblin_queue {
private:
	queue <int> left;
	queue <int> right;
	stack <int> middle;
public:
	void push_poor(const int& x);
	void push_rich(const int& x);
	int pop_first();
};

void Goblin_queue::push_poor(const int& x) {
	right.push(x);
	if (left.size() < right.size() + middle.size()) {
		if (!(middle.empty())) {
			left.push(middle.top());
			middle.pop();
		}
		else {
			left.push(right.front());
			right.pop();
		}
	}
}

void Goblin_queue::push_rich(const int& x) {
	if (left.size() == middle.size() + right.size()) {
		left.push(x);
	}
	else {
		middle.push(x);
	}
}

int Goblin_queue::pop_first() {
	int first = left.front();
	left.pop();
	if (left.size() < right.size() + middle.size()) {
		if (!(middle.empty())) {
			left.push(middle.top());
			middle.pop();
		}
		else {
			left.push(right.front());
			right.pop();
		}
	}
	return first;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Goblin_queue g_queue;
	size_t n;
	cin >> n;
	for (size_t i = 0; i < n; ++i) {
		char in;
		int ind;
		cin >> in;
		if (in == '+') {
			cin >> ind;
			g_queue.push_poor(ind);
		}
		else if (in == '*') {
			cin >> ind;
			g_queue.push_rich(ind);
		} else cout << g_queue.pop_first() << "\n";
	}
	return 0;
}