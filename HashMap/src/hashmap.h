#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "Arduino.h"

#include "hashnode.h"
#include "keyhash.h"
#include "keycomparator.h"

template <typename K, typename V, typename H, typename C>
class HashMap {
    private:
        uint8_t _size;
        uint8_t _buckets;

        HashNode<K, V>** _hashTable;
        H hash;
        C keyEquals;
    public:
        /**
         * CONSTRUCTORS.
         */
        HashMap(uint8_t buckets) {
            _buckets = buckets;
            _size = 0;

            _hashTable = new HashNode<K, V>*[buckets]();
        }

        ~HashMap() {
            for(uint8_t i = 0; i < _buckets; i++) {
                while(nullptr != _hashTable[i]) {
                    HashNode<K, V>* prev = _hashTable[i];
                    _hashTable[i] = _hashTable[i]->getNext();

                    delete prev;
                }
            }

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
        bool get(K key, V * value) {
            HashNode<K, V>* node = _hashTable[hash(key) % _buckets];

            while(nullptr != node && !keyEquals(key, node->getKey())) {
                node = node->getNext();
            }

            if(nullptr != node) {
                *value = node->getValue();
                return true;
            }

            return false;
        }

        void put(K key, V value) {
            uint8_t bucket = hash(key) % _buckets;

            HashNode<K, V>* prev = nullptr;
            HashNode<K, V>* node = _hashTable[bucket];

            while(nullptr != node && !keyEquals(key, node->getKey())) {
                prev = node;
                node = node->getNext();
            }

            if(nullptr == node) {
                // Create a new node.
                if(nullptr == prev) {
                    _hashTable[bucket] = new HashNode<K, V>(key, value);
                } else {
                    prev->setNext(new HashNode<K, V>(key, value));
                }

                _size++;
            } else {
                // Update an existing node.
                node->setValue(value);
            }
        }

        void remove(K key) {
            uint8_t bucket = hash(key) % _buckets;

            HashNode<K, V>* prev = nullptr;
            HashNode<K, V>* node = _hashTable[bucket];

            while(nullptr != node && !keyEquals(key, node->getKey())) {
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
