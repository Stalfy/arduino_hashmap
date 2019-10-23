#ifndef HASHNODE_H_
#define HASHNODE_H_

#include "Arduino.h"

class HashNode {
    private:
        int _key;
        int _value;
    public:
        HashNode(int key, int value);
        ~HashNode();

        int getValue();
};

#endif
