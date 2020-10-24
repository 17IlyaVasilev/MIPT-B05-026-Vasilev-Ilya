#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

class GDeque {
public:
	GDeque();
	~GDeque();
	GDeque operator= (GDeque) = delete;
	GDeque(const GDeque&) = delete;
	int pop();
	void push_poor(int x);
	void push_rich(int x);
private:
	deque <int> a;
	deque <int> b;
	
};
GDeque::GDeque() {
	deque <int> a;
	deque <int> b;
	
}
GDeque::~GDeque() {
	a.clear();
	b.clear();
	
}
int GDeque::pop() {
	int x = a.front();
	a.pop_front();
	if (b.size() > a.size()) {
		int p = b.front();
		b.pop_front();
		a.push_back(p);
		
	}
	return x;
	
}
void GDeque::push_poor(int x) {
	b.push_back(x);
	if (b.size() > a.size()) {
		int p = b.front();
		b.pop_front();
		a.push_back(p);
		
	}
	
}
void GDeque::push_rich(int x) {
	b.push_front(x);
	if (b.size() > a.size()) {
		int p = b.front();
		b.pop_front();
		a.push_back(p);
		
	}
	
}

int main() {
	int n, Number;
	char Input;
	GDeque Goblins;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> Input;
		if (Input == '-') {
			cout << Goblins.pop() << "\n";
			
		}
		else if (Input == '+') {
			cin >> Number;
			Goblins.push_poor(Number);
			
		}
		else {
			cin >> Number;
			Goblins.push_rich(Number);
			
		}
		
	}
	return 0;
	
}
