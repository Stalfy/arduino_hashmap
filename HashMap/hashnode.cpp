#include "hashnode.h"

HashNode::HashNode(int key, int value) {
    _key = key;
    _value = value;
    _next = nullptr;
}

HashNode::~HashNode() {
    Serial.print("Destroying node of key ");
    Serial.println(_key);
}

int HashNode::getKey() {
    return _key;
}

int HashNode::getValue() {
    return _value;
}

HashNode* HashNode::getNext() {
    return _next;
}

void HashNode::setValue(int value) {
    _value = value;
}

void HashNode::setNext(HashNode* next) {
    _next = next;
}
