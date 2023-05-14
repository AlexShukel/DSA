//
// Created by alexs on 2023-05-07.
// This hash table implemented as a set (values without duplicates and there is function has).
//

#ifndef DSA_HASHTABLE_H
#define DSA_HASHTABLE_H

#include <functional>
#include <vector>

template<class T>
struct Node {
    T value;
    Node *next = nullptr;

    explicit Node(const T &value) : value(value) {};
};

template<class T>
class HashTableSet {
private:
    std::function<long long(const T &)> hash;
    size_t size = 0;
    size_t capacity;
    size_t initialCapacity;
    std::vector<Node<T> *> table;

    size_t prehash(long long hashValue);

    void insertNodeInChain(Node<T> *&first, Node<T> *node);

    bool insertInChain(Node<T> *&first, const T &item);

    bool removeFromChain(Node<T> *&first, const T &item);

    bool hasInChain(Node<T> *slot, const T &item);

    void collectCurrentNodes(std::vector<Node<T> *> &nodes);

    void insertNodes(const std::vector<Node<T> *> &nodes);

    void growTable();

    void shrinkTable();

public:
    HashTableSet(const std::function<long long(const T &)> &hash, size_t initialCapacity);

    ~HashTableSet();

    void insert(const T &item);

    void remove(const T &item);

    bool has(const T &item);

    size_t getSize() const;

    size_t getCapacity() const;
};

// PUBLIC methods

template<class T>
HashTableSet<T>::HashTableSet(const std::function<long long(const T &)> &hash, size_t initialCapacity) {
    this->hash = hash;
    capacity = initialCapacity;
    this->initialCapacity = initialCapacity;
    table.resize(initialCapacity);
    std::fill(table.begin(), table.end(), nullptr);
}

template<class T>
HashTableSet<T>::~HashTableSet() {
    std::vector<Node<T> *> nodes;
    collectCurrentNodes(nodes);
    for (auto node: nodes) {
        delete node;
    }
}

template<class T>
size_t HashTableSet<T>::prehash(long long hashValue) {
    return hashValue % capacity;
}

template<class T>
size_t HashTableSet<T>::getSize() const {
    return size;
}

template<class T>
size_t HashTableSet<T>::getCapacity() const {
    return capacity;
}

template<class T>
void HashTableSet<T>::insert(const T &item) {
    size_t index = prehash(hash(item));
    bool inserted = insertInChain(table[index], item);
    if (inserted) {
        ++size;

        if (size == capacity) {
            growTable();
        }
    }
}

template<class T>
void HashTableSet<T>::remove(const T &item) {
    size_t index = prehash(hash(item));
    bool removed = removeFromChain(table[index], item);
    if (removed) {
        --size;

        if (capacity != initialCapacity && size < capacity / 4) {
            shrinkTable();
        }
    }
}

template<class T>
bool HashTableSet<T>::has(const T &item) {
    size_t index = prehash(hash(item));
    return hasInChain(table[index], item);
}

// PRIVATE methods

template<class T>
void HashTableSet<T>::insertNodeInChain(Node<T> *&first, Node<T> *node) {
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
bool HashTableSet<T>::insertInChain(Node<T> *&first, const T &item) {
    if (!first) {
        first = new Node<T>(item);
        return true;
    }

    Node<T> *current = first;

    if (current->value == item) {
        return false;
    }

    while (current->next) {
        if (current->value == item) {
            return false;
        }

        current = current->next;
    }
    current->next = new Node<T>(item);
    return true;
}

template<class T>
bool HashTableSet<T>::removeFromChain(Node<T> *&first, const T &item) {
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

    if (prev == current) {
        auto newHead = first->next;
        delete first;
        first = newHead;
        return true;
    }

    prev->next = current->next;
    delete current;
    return true;
}

template<class T>
bool HashTableSet<T>::hasInChain(Node<T> *slot, const T &item) {
    if (!slot) {
        return false;
    }

    while (slot && slot->value != item) {
        slot = slot->next;
    }

    return slot != nullptr;
}

template<class T>
void HashTableSet<T>::collectCurrentNodes(std::vector<Node<T> *> &nodes) {
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
void HashTableSet<T>::insertNodes(const std::vector<Node<T> *> &nodes) {
    for (auto node: nodes) {
        size_t index = prehash(hash(node->value));
        insertNodeInChain(table[index], node);
    }
}

template<class T>
void HashTableSet<T>::growTable() {
    std::vector<Node<T> *> nodes;
    collectCurrentNodes(nodes);

    capacity *= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

template<class T>
void HashTableSet<T>::shrinkTable() {
    std::vector<Node<T> *> nodes;
    collectCurrentNodes(nodes);

    capacity /= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

#endif //DSA_HASHTABLE_H
