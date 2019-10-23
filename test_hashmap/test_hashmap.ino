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
    testPutNoCollision();
    Serial.println("End test sequence.");    
}

void loop() {}

void testConstructor() {
    HashMap * hmap = new HashMap(3);

    assert(0 == hmap->getSize(), "Constructor default size.");
    assert(3 == hmap->getBuckets(), "Constructor buckets.");
    
    delete hmap;
}

void testPutNoCollision() {
    HashMap * hmap = new HashMap(3);

    assert(0 == hmap->getSize(), "PUT [size]     (no collision).");
    assert(-1 == hmap->get(0),   "PUT [Bucket 0] (no collision).");
    assert(-1 == hmap->get(1),   "PUT [Bucket 1] (no collision).");
    assert(-1 == hmap->get(2),   "PUT [Bucket 2] (no collision).");

    hmap->put(0, 0);
    hmap->put(2, 2);

    assert(2 == hmap->getSize(), "PUT [size]     (no collision).");
    assert(0 == hmap->get(0),    "PUT [Bucket 0] (no collision).");
    assert(2 == hmap->get(2),    "PUT [Bucket 2] (no collision).");

    delete hmap;
}
