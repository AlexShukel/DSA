//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_BSTMAP_HPP
#define DSA_BSTMAP_HPP

#include "Node.hpp"
#include "BstMapIterator.hpp"

template<class K, class T>
class BstMap {
private:
    Node<K, T> *root;
    size_t _size;

    Node<K, T> *findInorderSuccessor(Node<K, T> *node) const;

protected:
    Node<K, T> *removeImplementation(Node<K, T> *node);

    void setRoot(Node<K, T> *newRoot);

    Node<K, T> *getRoot();

    Node<K, T> *findNode(const K &key) const;

public:
    explicit BstMap();

    ~BstMap();

    virtual Node<K, T> *insert(const K &key, const T &value);

    virtual Node<K, T> *remove(const K &key);

    bool has(const K &key);

    T *get(const K &key);

    size_t size() const;

    BstMapIterator<K, T> getIterator(TraverseOrder order) const;
};

#include "BstMap.tpp"

#endif //DSA_BSTMAP_HPP
