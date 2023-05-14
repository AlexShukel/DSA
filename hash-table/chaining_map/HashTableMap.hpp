//
// Created by alexs on 2023-05-14.
//

#ifndef DSA_HASHTABLE_H
#define DSA_HASHTABLE_H

#include <functional>
#include <vector>

template<class K, class T>
struct Node {
    K key;
    T value;
    Node *next = nullptr;

    explicit Node(const K &key, const T &value) : key(key), value(value) {};
};

template<class K, class T>
class HashTableMap {
private:
    std::function<long long(const K &)> hash;
    size_t size = 0;
    size_t capacity;
    size_t initialCapacity;
    std::vector<Node<K, T> *> table;

    size_t prehash(long long hashValue);

    void insertNodeInChain(Node<K, T> *&first, Node<K, T> *node);

    bool insertInChain(Node<K, T> *&first, const K &key, const T &item);

    bool removeFromChain(Node<K, T> *&first, const K &key);

    T *getFromChain(Node<K, T> *slot, const K &key);

    void collectCurrentNodes(std::vector<Node<K, T> *> &nodes);

    void insertNodes(const std::vector<Node<K, T> *> &nodes);

    void growTable();

    void shrinkTable();

public:
    HashTableMap(const std::function<long long(const K &)> &hash, size_t initialCapacity);

    ~HashTableMap();

    void insert(const K &key, const T &item);

    void remove(const K &key);

    bool has(const K &key);

    T *get(const K &key);

    size_t getSize() const;

    size_t getCapacity() const;
};

// PUBLIC methods

template<class K, class T>
HashTableMap<K, T>::HashTableMap(const std::function<long long(const K &)> &hash, size_t initialCapacity) {
    this->hash = hash;
    this->capacity = initialCapacity;
    this->initialCapacity = initialCapacity;
    table.resize(initialCapacity);
    std::fill(table.begin(), table.end(), nullptr);
}

template<class K, class T>
HashTableMap<K, T>::~HashTableMap() {
    std::vector<Node<K, T> *> nodes;
    collectCurrentNodes(nodes);
    for (auto node: nodes) {
        delete node;
    }
}

template<class K, class T>
size_t HashTableMap<K, T>::getSize() const {
    return size;
}

template<class K, class T>
size_t HashTableMap<K, T>::getCapacity() const {
    return capacity;
}

template<class K, class T>
void HashTableMap<K, T>::insert(const K &key, const T &item) {
    size_t index = prehash(hash(key));
    bool addedNewKey = insertInChain(table[index], key, item);
    if (addedNewKey) {
        ++size;

        if (size == capacity) {
            growTable();
        }
    }
}

template<class K, class T>
void HashTableMap<K, T>::remove(const K &key) {
    size_t index = prehash(hash(key));
    bool removed = removeFromChain(table[index], key);
    if (removed) {
        --size;

        if (capacity != initialCapacity && size < capacity / 4) {
            shrinkTable();
        }
    }
}

template<class K, class T>
bool HashTableMap<K, T>::has(const K &key) {
    size_t index = prehash(hash(key));
    return getFromChain(table[index], key) != nullptr;
}

template<class K, class T>
T *HashTableMap<K, T>::get(const K &key) {
    size_t index = prehash(hash(key));
    return getFromChain(table[index], key);
}

// PRIVATE methods

template<class K, class T>
size_t HashTableMap<K, T>::prehash(long long hashValue) {
    return hashValue % capacity;
}

template<class K, class T>
void HashTableMap<K, T>::insertNodeInChain(Node<K, T> *&first, Node<K, T> *node) {
    if (!first) {
        first = node;
        return;
    }

    Node<K, T> *current = first;
    while (current->next) {
        current = current->next;
    }
    current->next = node;
}

template<class K, class T>
bool HashTableMap<K, T>::insertInChain(Node<K, T> *&first, const K &key, const T &item) {
    if (!first) {
        first = new Node<K, T>(key, item);
        return true;
    }

    Node<K, T> *current = first;

    if (first->key == key) {
        current->value = item;
        return false;
    }

    while (current->next) {
        if (current->key == key) {
            current->value = item;
            return false;
        }

        current = current->next;
    }

    current->next = new Node<K, T>(key, item);
    return true;
}

template<class K, class T>
bool HashTableMap<K, T>::removeFromChain(Node<K, T> *&first, const K &key) {
    if (!first) {
        return false;
    }

    Node<K, T> *prev = first;
    Node<K, T> *current = first;
    while (current && current->key != key) {
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

template<class K, class T>
T *HashTableMap<K, T>::getFromChain(Node<K, T> *slot, const K &key) {
    if (!slot) {
        return nullptr;
    }

    while (slot && slot->key != key) {
        slot = slot->next;
    }

    if (!slot) {
        return nullptr;
    }

    return &slot->value;
}

template<class K, class T>
void HashTableMap<K, T>::collectCurrentNodes(std::vector<Node<K, T> *> &nodes) {
    for (size_t i = 0; i < capacity; ++i) {
        auto current = table[i];
        Node<K, T> *prev = nullptr;

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

template<class K, class T>
void HashTableMap<K, T>::insertNodes(const std::vector<Node<K, T> *> &nodes) {
    for (auto node: nodes) {
        size_t index = prehash(hash(node->key));
        insertNodeInChain(table[index], node);
    }
}

template<class K, class T>
void HashTableMap<K, T>::growTable() {
    std::vector<Node<K, T> *> nodes;
    collectCurrentNodes(nodes);

    capacity *= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

template<class K, class T>
void HashTableMap<K, T>::shrinkTable() {
    std::vector<Node<K, T> *> nodes;
    collectCurrentNodes(nodes);

    capacity /= 2;
    table.resize(capacity);
    insertNodes(nodes);
}

#endif //DSA_HASHTABLE_H
