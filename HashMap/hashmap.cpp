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
        HashNode* node = _hashTable[i];

        while(nullptr != node) {
            HashNode* prev = node;
            node = node->getNext();

            delete prev;
            prev = nullptr;
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
    }
}

void HashMap::remove(int key) {
    uint8_t bucket = hash(key) % _buckets;
    HashNode * node = _hashTable[bucket];

    if(nullptr != node) {
        delete _hashTable[bucket];
        _hashTable[bucket] = nullptr;
        _size--;
    }
}
