#ifndef KEYHASH_H_
#define KEYHASH_H_

#include "Arduino.h"

template <typename K>
class KeyHash {
    public:
        KeyHash() {};
        virtual uint32_t operator() (K key) = 0;
};

#endif
