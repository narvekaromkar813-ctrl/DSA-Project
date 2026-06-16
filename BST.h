#ifndef BST_H
#define BST_H

#include "Threat.h"
#include <iostream>
#include <vector>

// Plain (unbalanced) Binary Search Tree, keyed by Threat::id.
// Provides Insert / Delete / Search / Inorder-Display as required by Module 1.
class BST {
private:
    struct Node {
        Threat data;
        Node* left;
        Node* right;
        explicit Node(const Threat& t) : data(t), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertRec(Node* node, const Threat& t) {
        if (!node) return new Node(t);
        if (t.id < node->data.id)       node->left  = insertRec(node->left, t);
        else if (t.id > node->data.id)  node->right = insertRec(node->right, t);
        else std::cout << "[BST] Duplicate ID " << t.id << ". Insert ignored.\n";
        return node;
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
            if (!node->left)  { Node* r = node->right; delete node; return r; }
            if (!node->right) { Node* l = node->left;  delete node; return l; }
            // Two children: replace with in-order successor
            Node* succ = findMin(node->right);
            node->data = succ->data;
            bool dummy = false;
            node->right = removeRec(node->right, succ->data.id, dummy);
        }
        return node;
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
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const Threat& t) { root = insertRec(root, t); }

    bool remove(int id) {
        bool removed = false;
        root = removeRec(root, id, removed);
        return removed;
    }

    // Returns a pointer to the live data inside the tree (or nullptr).
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
        if (all.empty()) { std::cout << "[BST] No records found.\n"; return; }
        Threat::displayHeader();
        for (const auto& t : all) t.display();
    }

    bool isEmpty() const { return root == nullptr; }
    int size() const { return static_cast<int>(getAllSorted().size()); }
};

#endif // BST_H
