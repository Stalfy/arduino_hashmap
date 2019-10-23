#include "hashnode.h"

HashNode::HashNode(int key, int value) {
    _key = key;
    _value = value;
}

HashNode::~HashNode() {
    Serial.print("Destroying node of key ");
    Serial.println(_key);
}
