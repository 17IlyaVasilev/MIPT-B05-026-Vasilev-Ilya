#include <iostream>
#include <algorithm>
#include <string>
#include<cstdlib>
#include<assert.h>

using namespace std;

const long long mil = 1000000;

class Heap {

public:

	Heap();
	~Heap();
	Heap operator= (Heap) = delete;
	Heap(const Heap&) = delete;

	void insert(long long x);
	long long getMin();
	void extractMin();
	void decreaseKey(long long i, long long d);

private:
	void growHeap();
	void siftUp(long long i);
	void siftDown(long long i);
	pair<long long, int>* heap_time = new pair<long long, int>[mil];
	long long* Ind = new long long[mil];
	long long BS = mil;
	int size = 0;
	int cnt = 1;
};

Heap::Heap() {
	pair<long long, int>* heap_time = new pair<long long, int>[mil];
	long long* Ind = new long long[mil];
	long long BS = mil;
	int size = 0;
	int cnt = 1;
}

Heap::~Heap() {
	delete[] heap_time;
	delete[] Ind;
}

void Heap::growHeap() {

	BS *= 2;
	pair<long long, int>* NB = new pair<long long, int>[BS];
	for (long long i = 0; i < size; ++i) {

		NB[i] = heap_time[i];

	}

	delete[] heap_time;
	heap_time = NB;

}


void Heap::insert(long long x) {

	if (size == BS)
		growHeap();
	heap_time[size] = { x,cnt };
	Ind[cnt] = size;
	siftUp(size);
	cnt++;
	size++;

}
long long Heap::getMin() {

	cnt++;
	return heap_time[0].first;

}

void Heap::extractMin() {

	size--;
	heap_time[0] = heap_time[size];
	Ind[heap_time[0].second] = 0;
	siftDown(0);
	cnt++;

}

void Heap::siftUp(long long x) {

	if ((x != 0) && (heap_time[((x + 1) / 2) - 1].first > heap_time[x].first)) {

		swap(heap_time[((x + 1) / 2) - 1], heap_time[x]);
		Ind[heap_time[((x + 1) / 2) - 1].second] = ((x + 1) / 2) - 1;
		Ind[heap_time[x].second] = x;
		siftUp(((x + 1) / 2) - 1);

	}

}

void Heap::siftDown(long long x) {

	if (2 * x + 1 < size)
		if (2 * x + 2 < size) {

			if (heap_time[2 * x + 1].first <= heap_time[2 * x + 2].first) {

				if (heap_time[x].first > heap_time[2 * x + 1].first) {

					swap(heap_time[x], heap_time[2 * x + 1]);
					Ind[heap_time[2 * x + 1].second] = 2 * x + 1;
					Ind[heap_time[x].second] = x;
					siftDown(2 * x + 1);

				}

			}

			else if (heap_time[x].first > heap_time[2 * x + 2].first) {

				swap(heap_time[x], heap_time[2 * x + 2]);
				Ind[heap_time[x].second] = x;
				Ind[heap_time[2 * x + 2].second] = 2 * x + 2;
				siftDown(2 * x + 2);

			}

		}

		else if (heap_time[x].first > heap_time[2 * x + 1].first) {

			swap(heap_time[x], heap_time[2 * x + 1]);
			Ind[heap_time[x].second] = x;
			Ind[heap_time[2 * x + 1].second] = 2 * x + 1;
			siftDown(2 * x + 1);

		}

}
void Heap::decreaseKey(long long x, long long d) {

	heap_time[Ind[x]].first -= d;
	siftUp(Ind[x]);
	cnt++;

}


int main() {

	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	Heap heap;
	long long q, b, c;
	string s;

	cin >> q;

	while (q > 0) {

		cin >> s;

		if (s == "insert") {

			cin >> b;
			heap.insert(b);

		}
		else if (s == "getMin") {

			long long temp = heap.getMin();
			cout << temp << '\n';

		}
		else if (s == "extractMin") {

			heap.extractMin();

		}
		else if (s == "decreaseKey") {

			cin >> b >> c;
			heap.decreaseKey(b, c);

		}

		q--;

	}

	return 0;

}