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

template<class T>
class HashTable {
private:
    std::function<long long(T)> hash;
    size_t size = 0;
    size_t capacity;
    size_t initialCapacity;
    std::vector<Node<T> *> table;

    size_t prehash(long long hashValue);

    void insertInChain(Node<T> *&first, Node<T> *node);

    bool removeFromChain(Node<T> *&first, const T &item);

    bool hasInChain(Node<T> *slot, const T &item);

    void collectCurrentNodes(std::vector<Node<T> *> &nodes);

    void insertNodes(const std::vector<Node<T> *> &nodes);

    void growTable();

    void shrinkTable();

public:
    HashTable(const std::function<long long(T)> &hash, size_t initialCapacity);

    void insert(const T &item);

    void remove(const T &item);

    bool has(const T &item);

    size_t getSize() const;

    size_t getCapacity() const;
};

// PUBLIC methods

template<class T>
HashTable<T>::HashTable(const std::function<long long(T)> &hash, size_t initialCapacity) {
    this->hash = hash;
    capacity = initialCapacity;
    this->initialCapacity = initialCapacity;
    table.resize(initialCapacity);
    std::fill(table.begin(), table.end(), nullptr);
}

template<class T>
size_t HashTable<T>::prehash(long long hashValue) {
    return hashValue % capacity;
}

template<class T>
size_t HashTable<T>::getSize() const {
    return size;
}

template<class T>
size_t HashTable<T>::getCapacity() const {
    return capacity;
}

template<class T>
void HashTable<T>::insert(const T &item) {
    if (size == capacity) {
        growTable();
    }

    size_t index = prehash(hash(item));
    insertInChain(table[index], new Node<T>(item));
    ++size;
}

template<class T>
void HashTable<T>::remove(const T &item) {
    if (capacity != initialCapacity && size < capacity / 4) {
        shrinkTable();
    }

    size_t index = prehash(hash(item));
    bool removed = removeFromChain(table[index], item);
    if (removed) {
        --size;
    }
}

template<class T>
bool HashTable<T>::has(const T &item) {
    size_t index = prehash(hash(item));
    return hasInChain(table[index], item);
}

// PRIVATE methods

template<class T>
void HashTable<T>::insertInChain(Node<T> *&first, Node<T> *node) {
    if (!first) {
        first = node;
        return;
    }

    Node<T> *current = first;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
}

template<class T>
bool HashTable<T>::removeFromChain(Node<T> *&first, const T &item) {
    if (!first) {
        return false;
    }

    Node<T> *prev = first;
    Node<T> *current = first;
    while (current && current->value != item) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        return false;
    }

    if (prev == first) {
        delete first;
        first = nullptr;
        return true;
    }

    prev->next = current->next;
    delete current;
    return true;
}

template<class T>
bool HashTable<T>::hasInChain(Node<T> *slot, const T &item) {
    if (!slot) {
        return false;
    }

    while (slot && slot->value != item) {
        slot = slot->next;
    }

    return static_cast<bool>(slot);
}

template<class T>
void HashTable<T>::collectCurrentNodes(std::vector<Node<T> *> &nodes) {
    size_t index = 0;

    for (size_t i = 0; i < capacity; ++i) {
        auto current = table[i];
        Node<T> *prev = nullptr;

        while (current) {
            nodes.push_back(current);

            if (prev) {
                prev->next = nullptr;
            }

            prev = current;
            current = current->next;
        }

        table[i] = nullptr;
    }
}

template<class T>
void HashTable<T>::insertNodes(const std::vector<Node<T> *> &nodes) {
    for (auto node: nodes) {
        size_t index = prehash(hash(node->value));
        insertInChain(table[index], node);
    }
}

template<class T>
void HashTable<T>::growTable() {
    std::vector<Node<T> *> nodes;
    collectCurrentNodes(nodes);

    capacity *= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

template<class T>
void HashTable<T>::shrinkTable() {
    std::vector<Node<T> *> nodes;
    collectCurrentNodes(nodes);

    capacity /= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

#endif //DSA_HASHTABLE_H
