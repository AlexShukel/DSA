//
// Created by alexs on 2023-03-06.
//

#ifndef DSA_BST_H
#define DSA_BST_H

#include <vector>
#include <stack>
#include <stdexcept>

/**
 * Declaration part
 */

enum TraverseOrder {
    INORDER,
    PREORDER,
    POSTORDER
};

template<class T>
struct Node {
    T value;
    Node *left;
    Node *right;

    explicit Node(T value);

    [[nodiscard]] bool isLeaf() const;
};

template<class T>
class BST_iterator {
private:
    std::stack<T> values;
public:
    BST_iterator(Node<T> *root, TraverseOrder order);

    BST_iterator &operator++();

    T &operator*();

    [[nodiscard]] bool hasNext() const;
};

template<class T>
class BST {
private:
    Node<T> *root;
public:
    explicit BST();

    explicit BST(std::vector<T>);

    ~BST();

    void insert(T value);

    void remove(T value);

    bool has(T value);

    size_t getHeight() const;

    size_t size() const;
};

/**
 * Implementation part
 */

template<class T>
Node<T>::Node(T value): value(value), left(nullptr), right(nullptr) {}

template<class T>
bool Node<T>::isLeaf() const {
    return left == nullptr && right == nullptr;
}

template<class T>
BST<T>::BST(): root(nullptr) {}

template<class T>
BST<T>::BST(std::vector<T>): root(nullptr) {
    // TODO: init tree according to the given vector
}

template<class T>
BST<T>::~BST() {
    // TODO: free memory
}

template<class T>
void BST<T>::insert(T value) {
    if (root == nullptr) {
        root = new Node(value);
    }

    Node<T> *parent = root;
    Node<T> *current = root;

    while (current != nullptr) {
        if (current->value == value) {
            break;
        }

        parent = current;

        if (current->value > value) {
            current = current->left;
        }

        if (current->value < value) {
            current = current->right;
        }
    }

    if (current == nullptr) {
        if (value > parent->value) {
            parent->right = new Node(value);
        } else {
            parent->left = new Node(value);
        }
    }
}

template<class T>
void BST<T>::remove(T value) {

}

template<class T>
bool BST<T>::has(T value) {
    return true;
}

template<class T>
size_t BST<T>::size() const {
    return 0;
}

template<class T>
size_t BST<T>::getHeight() const {
    return 0;
}

template<class T>
BST_iterator<T>::BST_iterator(Node<T> *root, TraverseOrder order) {
    switch (order) {
        case INORDER: {
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &[count, node] = tempStack.top();

                if (node->isLeaf()) {
                    values.push(node->value);
                    tempStack.pop();
                }

                if (count == 2) {
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    tempStack.push({0, node->right});
                }

                if (count == 1 && node->left) {
                    values.push(node->value);
                    tempStack.push({0, node->left});
                }

                ++count;
            }

            break;
        }

        case PREORDER: {
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &[count, node] = tempStack.top();

                if (node->isLeaf() || count == 2) {
                    values.push(node->value);
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    tempStack.push({0, node->right});
                }

                if (count == 1 && node->left) {
                    tempStack.push({0, node->left});
                }

                ++count;
            }

            break;
        }

        case POSTORDER: {
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &[count, node] = tempStack.top();

                if (node->isLeaf()) {
                    values.push(node->value);
                    tempStack.pop();
                }

                if (count == 2) {
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    values.push(node->value);
                    tempStack.push({0, node->right});
                }

                if (count == 1 && node->left) {
                    tempStack.push({0, node->left});
                }

                ++count;
            }

            break;
        }

        default: {
            throw std::invalid_argument("Invalid traverse order.");
        }
    }
}

template<class T>
BST_iterator<T> &BST_iterator<T>::operator++() {
    values.pop();
    return *this;
}

template<class T>
T &BST_iterator<T>::operator*() {
    return values.top();
}

template<class T>
bool BST_iterator<T>::hasNext() const {
    return !values.empty();
}

#endif //DSA_BST_H
