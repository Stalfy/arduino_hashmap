#include "hashmap.h"

#define assert(cond, desc) { _assert(cond, desc, __LINE__);  }
void _assert(bool cond, String desc, int line) {
    String info = "";
    info.concat(line);
    info.concat(": ");

    if(cond) {
        info.concat("[PASS] ");        
    } else {
        info.concat("[FAIL] ");
    }

    info.concat(desc);
    Serial.println(info);
}

void setup() {
    Serial.begin(9600);

    Serial.println("Begin test sequence.");
    testConstructor();
    Serial.println("End test sequence.");    
}

void loop() {}

void testConstructor() {
    HashMap * hmap = new HashMap(3);

    assert(0 == hmap->getSize(), "Constructor default size.");
    assert(3 == hmap->getBuckets(), "Constructor buckets.");
    
    delete hmap;
}
