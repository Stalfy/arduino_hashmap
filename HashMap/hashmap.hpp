#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_

#include "Arduino.h"

class HashMap {
    private:
        int _size;
        int _buckets;

    public:
        HashMap(int buckets);
        ~HashMap() {}

        int getBuckets();
        int getSize();
};

#endif
