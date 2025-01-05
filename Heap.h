#ifndef Heap_H
#define Heap_H

#include <iostream>
#include <vector>

using namespace std;

class Heap {
public:
    Heap(); 
    ~Heap();
    void insert(int value);
    void heapifyUp(int index);
    void show();
    void swap(int index1, int index2);
    void trier();
private:
    vector<int> heap;
};

#endif // Heap_H