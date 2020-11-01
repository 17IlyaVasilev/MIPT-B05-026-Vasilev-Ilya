#include <iostream>
#include <algorithm>

using namespace std;

const int DBS = 8;

class Heap {

public:
	Heap();
	Heap(int* b, int k);
	~Heap();
	Heap operator= (Heap) = delete;
	Heap(const Heap&) = delete;

	void insert(int x);
	int extractMax();
	void print(int k);

private:

	int* a = new int[DBS];
	int BS = DBS;
	int HS = 0;

	void growHeap();
	void siftUp(int x);
	void siftDown(int x);

};

Heap::Heap() {



}

Heap::Heap(int* b, int k) {

	for (int i = 0; i < k; i++) {

		if (HS == BS) {

			growHeap();

		}

		++HS;
		a[i] = b[i];

	}

	for (int i = k / 2; i >= 0; i--) {

		siftDown(i);

	}

}

Heap::~Heap() {

	delete[]a;

}

void Heap::growHeap(){

	BS *= 2;
	int* newB = new int[BS];

	for (int i = 0; i < HS; ++i) {

		newB[i] = a[i];

	}

	delete[] a;
	a = newB;

}


void Heap::siftUp(int x) {

	while (a[x] > a[(x - 1) / 2]) {

		swap(a[x], a[(x - 1) / 2]);
		x = (x - 1) / 2;

	}

}

void Heap::siftDown(int x) {

	while (2 * x + 1 < HS) {

		if (a[2 * x + 1] < a[2 * x + 2] && 2 * x + 2 < HS && a[2 * x + 2] > a[x]) {

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

	if (HS == BS) {

		growHeap();

	}

	a[HS] = x;
	siftUp(HS);
	HS++;

}

int Heap::extractMax() {

	int e = a[0];
	swap(a[0], a[HS - 1]);
	HS--;
	siftDown(0);

	return e;

}

void Heap::print(int k) {

	int* b = new int[k];

	for (int i = 0; i < k; i++) {

		b[k - 1 - i] = extractMax();

	}

	for (int i = 0; i < k; i++) {

		cout << b[i] << ' ';

	}

	delete[] b;

}

int main() {

	int n, k, c;
    cin >> n >> k;
	int* b = new int[k];

	for (int i = 0; i < k; i++) {

		cin >> b[i];

	}

	Heap heap(b, k);

	for (int i = k; i < n; i++) {

		cin >> c;
		heap.insert(c);
		heap.extractMax();

	}
	heap.print(k);

	delete[]b;

	return 0;

}
