#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "Arduino.h"
#include "hashnode.h"

class HashMap {
    private:
        int _size;
        int _buckets;

        HashNode ** _hashTable;
    public:
        HashMap(int buckets);
        ~HashMap();

        int getBuckets();
        int getSize();
};

#endif
