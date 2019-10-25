// Default operation assumes a uint32_t. 
// Based on the result from the hash prospector.
// https://github.com/skeeto/hash-prospector

#ifndef KEYHASH_H_
#define KEYHASH_H_

#include "Arduino.h"

template <typename K>
class KeyHash {
    public:
        KeyHash() {};
        uint32_t operator() (K key) {
            // exact bias: 0.020888578919738908

            uint32_t x = reinterpret_cast<uint32_t>(key);
            x ^= x >> 17;
            x *= reinterpret_cast<uint32_t>(0xed5ad4bb);
            x ^= x >> 11;
            x *= reinterpret_cast<uint32_t>(0xac4c1b51);
            x ^= x >> 15;
            x *= reinterpret_cast<uint32_t>(0x31848bab);
            x ^= x >> 14;

            return x;
        };
};

#endif
