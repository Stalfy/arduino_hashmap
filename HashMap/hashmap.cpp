#include "hashmap.hpp"

/**
 * CONSTRUCTORS.
 */
HashMap::HashMap(int buckets) {
    _buckets = buckets;
    _size = 0;
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
