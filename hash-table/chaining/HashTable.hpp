//
// Created by alexs on 2023-05-07.
//

#ifndef DSA_HASHTABLE_H
#define DSA_HASHTABLE_H

#include <functional>
#include <vector>

template<class T>
struct Node {
    T value;
    Node *next = nullptr;

    explicit Node(T value) : value(value) {};
};

template<class T, class K>
class HashTable {
private:
    // Function to convert item to key
    std::function<K(T, size_t)> hash;
    // Function to convert key to index
    std::function<size_t(K)> prehash;
    size_t size = 0;
    size_t capacity;
    std::vector<Node<T> *> table;

    void insertInChain(Node<T> *&first, const T &item);

    void removeFromChain(Node<T> *&first, const T &item);

    bool hasInChain(Node<T> *slot, const T &item);

public:
    HashTable(const std::function<size_t(T, size_t)> &hash, const std::function<size_t(K)> &prehash,
              size_t initialCapacity);

    void insert(const T &item);

    void remove(const T &item);

    bool has(const T &item);
};

// PUBLIC methods

template<class T, class K>
HashTable<T, K>::HashTable(const std::function<size_t(T, size_t)> &hash, const std::function<size_t(K)> &prehash,
                           size_t initialCapacity) {
    this->hash = hash;
    this->prehash = prehash;
    capacity = initialCapacity;
    table.resize(initialCapacity);
    std::fill(table.begin(), table.end(), nullptr);
}

template<class T, class K>
void HashTable<T, K>::insert(const T &item) {
    size_t index = prehash(hash(item, capacity));
    insertInChain(table[index], item);
}

template<class T, class K>
void HashTable<T, K>::remove(const T &item) {
    size_t index = prehash(hash(item, capacity));
    removeFromChain(table[index], item);
}

template<class T, class K>
bool HashTable<T, K>::has(const T &item) {
    size_t index = prehash(hash(item, capacity));
    return hasInChain(table[index], item);
}

// PRIVATE methods

template<class T, class K>
void HashTable<T, K>::insertInChain(Node<T> *&first, const T &item) {
    if (!first) {
        first = new Node<T>(item);
    }

    Node<T> *current = first;
    while (current->next) {
        current = current->next;
    }
    current->next = new Node<T>(item);
}

template<class T, class K>
void HashTable<T, K>::removeFromChain(Node<T> *&first, const T &item) {
    if (!first) {
        return;
    }

    Node<T> *prev = first;
    Node<T> *current = first;
    while (current && current->value != item) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        return;
    }

    if (prev == first) {
        delete first;
        first = nullptr;
        return;
    }

    prev->next = current->next;
    delete current;
}

template<class T, class K>
bool HashTable<T, K>::hasInChain(Node<T> *slot, const T &item) {
    if (!slot) {
        return false;
    }

    while (slot && slot->value != item) {
        slot = slot->next;
    }

    return static_cast<bool>(slot);
}

#endif //DSA_HASHTABLE_H
