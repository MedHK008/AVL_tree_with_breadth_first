#include "BinaryTree.h"
#include <fstream>
#include <iostream>
#include <chrono>

int main() {
    BinaryTree tree;

    std::ifstream file("text.txt");

    string value;
    const chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    while (file >> value) {
        tree.insert(value);
    }

    const chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::duration<double>>(end - begin).count() << "[s]" << endl;

    file.close();


    cout << "Preorder traversal of the constructed AVL tree is \n";
    tree.preOrder();

    cout << "breadth first traversal of the constructed AVL tree is \n";
    tree.breadthFirst();
}
