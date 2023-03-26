//
// Created by alexs on 2023-03-11.
//

#ifndef DSA_BSTITERATOR_HPP
#define DSA_BSTITERATOR_HPP

#include "Node.hpp"

enum TraverseOrder {
    INORDER,
    PREORDER,
    POSTORDER
};

template<class T>
class BstIterator {
private:
    std::stack<Node<T> *> values;
public:
    BstIterator(Node<T> *root, TraverseOrder order);

    BstIterator &operator++();

    Node<T> *getNode() const;

    T getValue() const;

    [[nodiscard]] bool hasNext() const;
};

template<class T>
BstIterator<T>::BstIterator(Node<T> *root, TraverseOrder order) {
    switch (order) {
        // LVD (left, vertex, right)
        case INORDER: {
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<T> *node = t.second;

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
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<T> *node = t.second;

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
            std::stack<std::pair<int, Node<T> *>> tempStack;
            tempStack.push({0, root});

            while (!tempStack.empty()) {
                auto &t = tempStack.top();

                int &count = t.first;
                Node<T> *node = t.second;

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

template<class T>
BstIterator<T> &BstIterator<T>::operator++() {
    values.pop();
    return *this;
}

template<class T>
Node<T> *BstIterator<T>::getNode() const {
    return values.top();
}

template<class T>
T BstIterator<T>::getValue() const {
    return values.top()->value;
}

template<class T>
bool BstIterator<T>::hasNext() const {
    return !values.empty();
}

#endif //DSA_BSTITERATOR_HPP
