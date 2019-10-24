#ifndef HASHNODE_H_
#define HASHNODE_H_

#include "Arduino.h"

class HashNode {
    private:
        int _key;
        int _value;
        HashNode* _next;
    public:
        HashNode(int key, int value);
        ~HashNode();

        int getKey();
        int getValue();
        HashNode* getNext();

        void setValue(int value);
        void setNext(HashNode* next);
};

#endif
