//
// Created by alexs on 2023-06-04.
//

#ifndef DSA_AVLMAP_HPP
#define DSA_AVLMAP_HPP

#include "BstMap.hpp"

template<class K, class T>
struct NodeOverflow {
    Node<K, T> *X;
    Node<K, T> *Z;

    NodeOverflow(Node<K, T> *X, Node<K, T> *Z): X(X), Z(Z) {};
};

template<class K, class T>
class AvlMap : public BstMap<K, T> {
private:
    void updateBalanceFactors(Node<K, T> *from);

    NodeOverflow<K, T> findOverflowedNode(Node<K, T> *from);

public:
    explicit AvlMap() = default;

    Node<K, T> *insert(const K &key, const T &value) override;

    void remove(const K &key) override;
};

#include "AvlMap.tpp"

#endif //DSA_AVLMAP_HPP
