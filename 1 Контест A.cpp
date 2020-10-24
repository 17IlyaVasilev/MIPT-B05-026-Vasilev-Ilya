#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <string>

using namespace std;

class stack {
public:
	stack();
	~stack();
	stack operator= (stack) = delete;
	stack(const stack&) = delete;
	void push(int x);
	int pop();
	int back();
	int size();
	
private:
	struct Node {
		int value;
		Node* next;
		
	};
	Node* head;
	int length;
	
};

stack::stack() {
	length = 0;
	head = nullptr;
	
}

stack::~stack() {
	while (head != nullptr) {
		length--;
		Node* NTD = head;
		head = head->next;
		delete NTD;
		
	}
	
}

void stack::push(int x) {
	length++;
	Node* temp = new Node;
	temp->next = head;
	temp->value = x;
	head = temp;
	
}

int stack::pop() {
	assert(length != 0);
	length--;
	int rValue = head->value;
	Node* NTD = head;
	head = head->next;
	delete NTD;
	return rValue;
	
}

int stack::back() {
	assert(length);
	return head->value;
	
}

int stack::size() {
	return length;
	
}


int main()
{
	int n;
	stack Stack;
	string Input;
	while (Input != "exit") {
		cin >> Input;
		if (Input == "push") {
			cin >> n;
			Stack.push(n);
			cout << "ok" << endl;

		}
		else
			if (Input == "pop") {
				if (Stack.size() != 0) {
					cout << Stack.pop() << endl;

				}
				else {
					cout << "error" << endl;

				}

			}
			else if (Input == "back") {
				if (Stack.size()) {
					cout << Stack.back() << endl;

				}
				else {
					cout << "error" << endl;

				}

			}
			else if (Input == "size") {
				cout << Stack.size() << endl;

			}
			else if (Input == "clear") {
				Stack.~stack();
				cout << "ok" << endl;

			}

	}
	cout << "bye"
}