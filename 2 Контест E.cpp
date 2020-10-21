#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Heap {

public:

	Heap();
	~Heap();
	Heap operator= (Heap) = delete;
	Heap(const Heap&) = delete;

	int* a;
	void siftUp(int x);
	void siftDown(int x);
	void insert(int x);
	int extractMax();

private:

	int Size = 0;

};

Heap::Heap() {

}

Heap::~Heap() {

}


void Heap::siftUp(int x) {

	while (a[x] > a[(x - 1) / 2]) {

		swap(a[x], a[(x - 1) / 2]);
		x = (x - 1) / 2;

	}

}

void Heap::siftDown(int x) {

	while (2 * x + 1 < Size) {

		if (a[2 * x + 1] < a[2 * x + 2] && 2 * x + 2 < Size && a[2 * x + 2] > a[x]) {

			swap(a[2 * x + 2], a[x]);
			x = 2 * x + 2;

		}

		else if (a[2 * x + 1] > a[x]) {

			swap(a[2 * x + 1], a[x]);
			x = 2 * x + 1;

		}

		else break;

	}

}

void Heap::insert(int x) {

	a[Size] = x;
	siftUp(Size);
	Size++;

}

int Heap::extractMax() {

	int e = a[0];
	swap(a[0], a[Size - 1]);
	Size--;
	siftDown(0);

	return e;

}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, k, c;
	Heap heap;
	cin >> n >> k;
	int* b = new int[k];
	heap.a = new int[n];

	for (int i = 0; i < k; i++) {

		cin >> c;
		heap.insert(c);

	}

	for (int i = k; i < n; i++) {

		cin >> c;
		heap.insert(c);
		heap.extractMax();

	}

	for (int i = 0; i < k; i++)
		b[k - 1 - i] = heap.extractMax();

	for (int i = 0; i < k; i++)
		cout << b[i] << ' ';

	delete[] b;
	delete[] heap.a;

	return 0;

}