//
// Created by alexs on 2023-03-11.
//

#ifndef DSA_BSTITERATOR_HPP
#define DSA_BSTITERATOR_HPP

#include "Node.hpp"
#include <stack>
#include <stdexcept>

enum TraverseOrder {
    INORDER,
    PREORDER,
    POSTORDER,
};

template<class K, class T>
class BstMapIterator {
private:
    std::stack<Node<K, T> *> values;
public:
    BstMapIterator(Node<K, T> *root, TraverseOrder order);

    BstMapIterator &operator++();

    Node<K, T> *getNode() const;

    [[nodiscard]] bool hasNext() const;
};

template<class K, class T>
BstMapIterator<K, T>::BstMapIterator(Node<K, T> *root, TraverseOrder order) {
    if (!root) {
        return;
    }

    switch (order) {
        // LVD (left, vertex, right)
        case INORDER: {
            std::stack<std::pair<int, Node<K, T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<K, T> *node = t.second;

                if (node->isLeaf()) {
                    values.push(node);
                    tempStack.pop();
                }

                if (count == 2) {
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    tempStack.push({0, node->right});
                }

                if (count == 1 && node->left) {
                    values.push(node);
                    tempStack.push({0, node->left});
                }

                ++count;
            }

            break;
        }

            // VLR (vertex, left, right)
        case PREORDER: {
            std::stack<std::pair<int, Node<K, T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<K, T> *node = t.second;

                if (node->isLeaf() || count == 2) {
                    values.push(node);
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

            // LRV (left, right, vertex)
        case POSTORDER: {
            std::stack<std::pair<int, Node<K, T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<K, T> *node = t.second;

                if (node->isLeaf()) {
                    values.push(node);
                    tempStack.pop();
                }

                if (count == 2) {
                    tempStack.pop();
                }

                if (count == 0 && node->right) {
                    values.push(node);
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

template<class K, class T>
BstMapIterator<K, T> &BstMapIterator<K, T>::operator++() {
    values.pop();
    return *this;
}

template<class K, class T>
Node<K, T> *BstMapIterator<K, T>::getNode() const {
    return values.top();
}

template<class K, class T>
bool BstMapIterator<K, T>::hasNext() const {
    return !values.empty();
}

#endif //DSA_BSTITERATOR_HPP
