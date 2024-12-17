//
// Created by med on 12/16/2024.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

struct Tree {
    string value;
    struct Tree *left;
    struct Tree *right;
    int height;
    explicit Tree(string value) {
        this->value = std::move(value);
        this->left = nullptr;
        this->right = nullptr;
        this->height = 1;
    }
};

class BinaryTree {
    struct Tree *root;
    public:
    static int getHeight(struct Tree *node) {
        return node == nullptr ? 0 : node->height;
    }

    static int getBalanceFactor(struct Tree *node) {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    Tree* rotateRight(struct Tree *y) {
        struct Tree *x = y->left;
        struct Tree *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Tree* rotateLeft(struct Tree *x) {
        /// Rotate Right
        struct Tree *y = x->right;
        struct Tree *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Tree* insert(Tree* node, const string& value){
        if (node == nullptr) {
            return new Tree(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else if (value > node->value) {
            node->right = insert(node->right, value);
        } else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalanceFactor(node);

        if (balance > 1 /*&& value < node->left->value*/) {
            return rotateRight(node);
        }

        if (balance < -1 /*&& value > node->right->value*/) {
            return rotateLeft(node);
        }

        // if (balance > 1 && value > node->left->value) {
        //     node->left = rotateLeft(node->left);
        //     return rotateRight(node);
        // }

        // if (balance < -1 && value < node->right->value) {
        //     node->right = rotateRight(node->right);
        //     return rotateLeft(node);
        // }

        return node;
    }

    void preOrder(const struct Tree *node) {
        if (node != nullptr) {
            cout << node->value << " " << node->height << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    public: 
    BinaryTree() {
        root = nullptr;
    }

    void insert(const string& value) {
        root = insert(root, value);
    }

    void preOrder() {
        preOrder(root);
        cout << endl;
    }

    void breadthFirst() const {
        if (root == nullptr) {
            return;
        }

        queue<Tree*> q;
        q.push(root);

        while (!q.empty()) {
            const struct Tree *node = q.front();
            cout << node->value << " ";
            q.pop();

            if (node->left != nullptr) {
                q.push(node->left);
            }

            if (node->right != nullptr) {
                q.push(node->right);
            }
        }

        cout << endl;
    }
};



#endif //BINARYTREE_H
