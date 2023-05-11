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
    size_t initialCapacity;
    std::vector<Node<T> *> table;

    void insertInChain(Node<T> *&first, Node<T> *node);

    bool removeFromChain(Node<T> *&first, const T &item);

    bool hasInChain(Node<T> *slot, const T &item);

    void collectCurrentNodes(std::vector<Node<T> *> &nodes);

    void insertNodes(const std::vector<Node<T> *> &nodes);

    void growTable();

    void shrinkTable();

public:
    HashTable(const std::function<size_t(T, size_t)> &hash, const std::function<size_t(K)> &prehash,
              size_t initialCapacity);

    void insert(const T &item);

    void remove(const T &item);

    bool has(const T &item);

    size_t getSize() const;

    size_t getCapacity() const;
};

// PUBLIC methods

template<class T, class K>
HashTable<T, K>::HashTable(const std::function<size_t(T, size_t)> &hash, const std::function<size_t(K)> &prehash,
                           size_t initialCapacity) {
    this->hash = hash;
    this->prehash = prehash;
    capacity = initialCapacity;
    this->initialCapacity = initialCapacity;
    table.resize(initialCapacity);
    std::fill(table.begin(), table.end(), nullptr);
}

template<class T, class K>
size_t HashTable<T, K>::getSize() const {
    return size;
}

template<class T, class K>
size_t HashTable<T, K>::getCapacity() const {
    return capacity;
}

template<class T, class K>
void HashTable<T, K>::insert(const T &item) {
    if (size == capacity) {
        growTable();
    }

    size_t index = prehash(hash(item, capacity));
    insertInChain(table[index], new Node<T>(item));
    ++size;
}

template<class T, class K>
void HashTable<T, K>::remove(const T &item) {
    if (capacity != initialCapacity && size < capacity / 4) {
        shrinkTable();
    }

    size_t index = prehash(hash(item, capacity));
    bool removed = removeFromChain(table[index], item);
    if (removed) {
        --size;
    }
}

template<class T, class K>
bool HashTable<T, K>::has(const T &item) {
    size_t index = prehash(hash(item, capacity));
    return hasInChain(table[index], item);
}

// PRIVATE methods

template<class T, class K>
void HashTable<T, K>::insertInChain(Node<T> *&first, Node<T> *node) {
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

template<class T, class K>
bool HashTable<T, K>::removeFromChain(Node<T> *&first, const T &item) {
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

template<class T, class K>
void HashTable<T, K>::collectCurrentNodes(std::vector<Node<T> *> &nodes) {
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

template<class T, class K>
void HashTable<T, K>::insertNodes(const std::vector<Node<T> *> &nodes) {
    for (auto node: nodes) {
        size_t index = prehash(hash(node->value, capacity));
        insertInChain(table[index], node);
    }
}

template<class T, class K>
void HashTable<T, K>::growTable() {
    std::vector<Node<T> *> nodes;
    collectCurrentNodes(nodes);

    capacity *= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

template<class T, class K>
void HashTable<T, K>::shrinkTable() {
    std::vector<Node<T> *> nodes;
    collectCurrentNodes(nodes);

    capacity /= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

#endif //DSA_HASHTABLE_H
