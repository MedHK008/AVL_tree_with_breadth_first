#include "Heap.h"

#include <algorithm>

Heap::Heap() {
}

Heap::~Heap() {
    heap.clear();
}

void Heap::insert(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

void Heap::heapifyUp(int index) {
    if (index <= 1) {
        return;
    }
    int parentIndex = index/2;
    if (heap[index] > heap[parentIndex]) {
        swap(index, parentIndex);
        heapifyUp(parentIndex);
    }
}

void Heap::show() {
    for (int i = 1; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

void Heap::swap(int index1, int index2) {
    int temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}

void Heap::trier() {
    sort(heap.begin(), heap.end());
}
