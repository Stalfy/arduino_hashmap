#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "Arduino.h"
#include "hashnode.h"

class HashMap {
    private:
        uint8_t _size;
        uint8_t _buckets;

        HashNode ** _hashTable;
        uint32_t hash(int key);
    public:
        HashMap(uint8_t buckets);
        ~HashMap();

        uint8_t getBuckets();
        uint8_t getSize();

        int get(int key);
        void put(int key, int value);
        void remove(int key);
};

#endif
