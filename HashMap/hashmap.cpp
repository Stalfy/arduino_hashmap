#include "hashmap.h"

/**
 * CONSTRUCTORS.
 */
HashMap::HashMap(uint8_t buckets) {
    _buckets = buckets;
    _size = 0;

    _hashTable = new HashNode*[buckets]();
}

HashMap::~HashMap() {
    Serial.println("Destroying contents of this HashMap.");
    
    for(uint8_t i = 0; i < _buckets; i++) {
        while(nullptr != _hashTable[i]) {
            HashNode* prev = _hashTable[i];
            _hashTable[i] = _hashTable[i]->getNext();

            delete prev;
        }
    }

    Serial.println("Destroying this HashMap.");
    delete[] _hashTable;
    _hashTable = nullptr;
}

/**
 * GETTERS.
 */
uint8_t HashMap::getBuckets() {
    return _buckets;
}

uint8_t HashMap::getSize() {
    return _size;
}

/**
 * PRIVATE METHODS.
 */
uint32_t HashMap::hash(int key) {
    return key;
}

/**
 * MAP OPERATIONS.
 */
int HashMap::get(int key) {
    HashNode * node = _hashTable[hash(key) % _buckets];

    while(nullptr != node && key != node->getKey()) {
        node = node->getNext();
    }

    if(nullptr != node) {
        return node->getValue();
    }

    return -1;
}

void HashMap::put(int key, int value) {
    uint8_t bucket = hash(key) % _buckets;

    HashNode* prev = nullptr;
    HashNode* node = _hashTable[bucket];

    while(nullptr != node && key != node->getKey()) {
        prev = node;
        node = node->getNext();
    }

    if(nullptr == node) {
        // Create a new node.
        if(nullptr == prev) {
            _hashTable[bucket] = new HashNode(key, value);
        } else {
            prev->setNext(new HashNode(key, value));
        }

        _size++;
    } else {
        // Update an existing node.
        node->setValue(value);
    }
}

void HashMap::remove(int key) {
    uint8_t bucket = hash(key) % _buckets;
    
    HashNode* prev = nullptr;
    HashNode* node = _hashTable[bucket];

    while(nullptr != node && key != node->getKey()) {
        prev = node;
        node = node->getNext();
    }

    if(nullptr != node) {
        if(nullptr == prev) {
            if(nullptr == node->getNext()) {
                // Remove a bucket node.
                delete _hashTable[bucket];
                _hashTable[bucket] = nullptr;
            } else {
                // Remove a list head node.
                _hashTable[bucket] = node->getNext();
                delete node;
                node = nullptr;
            }
        } else {
            if(nullptr == node->getNext()) {
                // Remove a list tail node.
            } else {
                // Remove a list body node.
                prev->setNext(node->getNext());
                delete node;
                node = nullptr;
            }
        }

        _size--;
    }
}
