#ifndef AVLTREE_H
#define AVLTREE_H

#include "Threat.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Self-balancing AVL Tree, keyed by Threat::id.
// Guarantees O(log n) Insert / Delete / Search even under adversarial input order.
class AVLTree {
private:
    struct Node {
        Threat data;
        Node* left;
        Node* right;
        int height;
        explicit Node(const Threat& t) : data(t), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* n) const { return n ? n->height : 0; }
    int balanceFactor(Node* n) const { return n ? height(n->left) - height(n->right) : 0; }
    void updateHeight(Node* n) { n->height = 1 + std::max(height(n->left), height(n->right)); }

    Node* rotateRight(Node* y) {
        Node* x  = y->left;
        Node* t2 = x->right;
        x->right = y;
        y->left  = t2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y  = x->right;
        Node* t2 = y->left;
        y->left  = x;
        x->right = t2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = balanceFactor(node);
        if (bf > 1) { // left heavy
            if (balanceFactor(node->left) < 0) node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1) { // right heavy
            if (balanceFactor(node->right) > 0) node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node* insertRec(Node* node, const Threat& t) {
        if (!node) return new Node(t);
        if (t.id < node->data.id)       node->left  = insertRec(node->left, t);
        else if (t.id > node->data.id)  node->right = insertRec(node->right, t);
        else { std::cout << "[AVL] Duplicate ID " << t.id << ". Insert ignored.\n"; return node; }
        return balance(node);
    }

    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* removeRec(Node* node, int id, bool& removed) {
        if (!node) return nullptr;
        if (id < node->data.id) {
            node->left = removeRec(node->left, id, removed);
        } else if (id > node->data.id) {
            node->right = removeRec(node->right, id, removed);
        } else {
            removed = true;
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            Node* succ = findMin(node->right);
            node->data = succ->data;
            bool dummy = false;
            node->right = removeRec(node->right, succ->data.id, dummy);
        }
        return balance(node);
    }

    Node* searchRec(Node* node, int id) const {
        if (!node) return nullptr;
        if (id == node->data.id) return node;
        return (id < node->data.id) ? searchRec(node->left, id) : searchRec(node->right, id);
    }

    void inorderRec(Node* node, std::vector<Threat>& out) const {
        if (!node) return;
        inorderRec(node->left, out);
        out.push_back(node->data);
        inorderRec(node->right, out);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    void insert(const Threat& t) { root = insertRec(root, t); }

    bool remove(int id) {
        bool removed = false;
        root = removeRec(root, id, removed);
        return removed;
    }

    Threat* search(int id) const {
        Node* n = searchRec(root, id);
        return n ? &n->data : nullptr;
    }

    std::vector<Threat> getAllSorted() const {
        std::vector<Threat> out;
        inorderRec(root, out);
        return out;
    }

    void displayAll() const {
        std::vector<Threat> all = getAllSorted();
        if (all.empty()) { std::cout << "[AVL] No records found.\n"; return; }
        Threat::displayHeader();
        for (const auto& t : all) t.display();
    }

    bool isEmpty() const { return root == nullptr; }
    int size() const { return static_cast<int>(getAllSorted().size()); }
};

#endif // AVLTREE_H
