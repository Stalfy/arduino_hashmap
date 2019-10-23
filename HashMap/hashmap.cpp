#include "hashmap.h"

/**
 * CONSTRUCTORS.
 */
HashMap::HashMap(int buckets) {
    _buckets = buckets;
    _size = 0;

    _hashTable = new HashNode*[buckets];
}

HashMap::~HashMap() {
    Serial.println("Destroying this HashMap.");
    delete[] _hashTable;
}

/**
 * GETTERS.
 */
int HashMap::getBuckets() {
    return _buckets;
}

int HashMap::getSize() {
    return _size;
}
