#ifndef HASHNODE_H_
#define HASHNODE_H_

#include "Arduino.h"

template <typename K, typename V>
class HashNode {
    private:
        K _key;
        V _value;
        HashNode<K, V>* _next;
    public:
        // Constructors.
        HashNode(K key, V value) {
            _key = key;
            _value = value;
            _next = nullptr;        
        }

        ~HashNode() {
            Serial.print("Destroying node of key ");
            Serial.println(_key);
        }

        // Getters.
        K getKey() {
            return _key;
        }

        V getValue() {
            return _value;
        }

        HashNode<K, V>* getNext() {
            return _next;
        }

        // Setters.
        void setValue(V value) {
            _value = value;
        }

        void setNext(HashNode* next) {
            _next = next;
        }
};

#endif
