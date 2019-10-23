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
        delete _hashTable[i];
    }

    Serial.println("Destroying this HashMap.");
    delete[] _hashTable;
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

    if(nullptr != node) {
        return node->getValue();
    }

    return -1;
}

void HashMap::put(int key, int value) {
    uint8_t bucket = hash(key) % _buckets;
    HashNode * node = _hashTable[bucket];

    if(nullptr == node) {
        _hashTable[bucket] = new HashNode(key, value);
        _size++;
    }
}
