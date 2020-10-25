#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int BS = 1000000;

class Heap {

public:

	Heap();
	~Heap();
	Heap operator= (Heap) = delete;
	Heap(const Heap&) = delete;

	void siftUp(int x);
	void siftDown(int x);
	void insert(int x);
	int extractMax();
	void print(int k);

private:

	int* a = new int[BS];
	int* b = new int[BS];
	int bufferSize = BS;
	int heapSize = 0;

	void growHeap();

};

Heap::Heap() {



}

Heap::~Heap() {

	delete[] a;
	delete[] b;

}

void Heap::growHeap()
{

	bufferSize *= 2;
	int* newB = new int[bufferSize];
	for (int i = 0; i < heapSize; ++i) {

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

	while (2 * x + 1 < heapSize) {

		if (a[2 * x + 1] < a[2 * x + 2] && 2 * x + 2 < heapSize && a[2 * x + 2] > a[x]) {

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

	if (heapSize == bufferSize) {

		growHeap();

	}

	a[heapSize] = x;
	siftUp(heapSize);
	heapSize++;

}

int Heap::extractMax() {

	int q = a[0];
	swap(a[0], a[heapSize - 1]);
	heapSize--;
	siftDown(0);

	return q;

}

void Heap::print(int k) {

	for (int i = 0; i < k; i++) {

		b[k - 1 - i] = extractMax();

	}

	for (int i = 0; i < k; i++) {

		cout << b[i] << ' ';

	}

}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, k, c;
	Heap heap;
	cin >> n >> k;

	for (int i = 0; i < k; i++) {

		cin >> c;
		heap.insert(c);

	}

	for (int i = k; i < n; i++) {

		cin >> c;
		heap.insert(c);
		heap.extractMax();

	}

	heap.print(k);

	return 0;

}
