//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_BSTMAP_HPP
#define DSA_BSTMAP_HPP

#include "Node.hpp"

template<class K, class T>
class BstMap {
private:
    Node<K, T> *root;
    size_t _size;

    Node<K, T> *findNode(const K &key) const;

    Node<K, T> *findInorderSuccessor(Node<K, T> *node) const;

    Node<K, T> *removeImplementation(Node<K, T> *node);

public:
    explicit BstMap();

    virtual Node<K, T> *insert(const K &key, const T &value);

    virtual void remove(const K &key);

    bool has(const K &key);

    T *get(const K &key);

    size_t size() const;
};

#include "BstMap.tpp"

#endif //DSA_BSTMAP_HPP
