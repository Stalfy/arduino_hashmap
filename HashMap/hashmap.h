#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "Arduino.h"
#include "hashnode.h"

class HashMap {
    private:
        uint8_t _size;
        uint8_t _buckets;
        HashNode<int, int>** _hashTable;

        /**
         * UTILITY METHODS.
         */
        uint32_t hash(int key) {
            return key;
        }
    public:
        /**
         * CONSTRUCTORS.
         */
        HashMap(uint8_t buckets) {
            _buckets = buckets;
            _size = 0;

            _hashTable = new HashNode<int, int>*[buckets]();
        }

        ~HashMap() {
            Serial.println("Destroying contents of this HashMap.");

            for(uint8_t i = 0; i < _buckets; i++) {
                while(nullptr != _hashTable[i]) {
                    HashNode<int, int>* prev = _hashTable[i];
                    _hashTable[i] = _hashTable[i]->getNext();

                    delete prev;
                }
            }

            Serial.println("Destroying this HashMap.");
            delete[] _hashTable;
            _hashTable = nullptr;
        }

        /**
         * GETTERS.
         */
        uint8_t getBuckets() {
            return _buckets;
        }

        uint8_t getSize() {
            return _size;
        }

        /**
         * MAP OPERATIONS.
         */
        int get(int key) {
            HashNode<int, int>* node = _hashTable[hash(key) % _buckets];

            while(nullptr != node && key != node->getKey()) {
                node = node->getNext();
            }

            if(nullptr != node) {
                return node->getValue();
            }

            return -1;
        }

        void put(int key, int value) {
            uint8_t bucket = hash(key) % _buckets;

            HashNode<int, int>* prev = nullptr;
            HashNode<int, int>* node = _hashTable[bucket];

            while(nullptr != node && key != node->getKey()) {
                prev = node;
                node = node->getNext();
            }

            if(nullptr == node) {
                // Create a new node.
                if(nullptr == prev) {
                    _hashTable[bucket] = new HashNode<int, int>(key, value);
                } else {
                    prev->setNext(new HashNode<int, int>(key, value));
                }

                _size++;
            } else {
                // Update an existing node.
                node->setValue(value);
            }
        }

        void remove(int key) {
            uint8_t bucket = hash(key) % _buckets;

            HashNode<int, int>* prev = nullptr;
            HashNode<int, int>* node = _hashTable[bucket];

            while(nullptr != node && key != node->getKey()) {
                prev = node;
                node = node->getNext();
            }

            if(nullptr != node) {
                if(nullptr == prev) {
                    if(nullptr == node->getNext()) {
                        // Remove a bucket node.
                        _hashTable[bucket] = nullptr;
                    } else {
                        // Remove a list head node.
                        _hashTable[bucket] = node->getNext();
                    }
                } else {
                    if(nullptr == node->getNext()) {
                        // Remove a list tail node.
                        prev->setNext(nullptr);
                    } else {
                        // Remove a list body node.
                        prev->setNext(node->getNext());
                    }
                }

                delete node;
                _size--;
            }
        }
};

#endif
