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
    testPutCollision();
    testUpdateNoCollision();
    testUpdateCollision();
    testRemoveNoCollision();
    testRemoveCollisionHead();
    Serial.println("End test sequence.");    
}

void loop() {}

void testConstructor() {
    HashMap * hmap = new HashMap(3);

    assert(0 == hmap->getSize(), "Constructor default size.");
    assert(3 == hmap->getBuckets(), "Constructor buckets.");

    assert(-1 == hmap->get(0), "Constructor [Bucket 0].");
    assert(-1 == hmap->get(1), "Constructor [Bucket 1].");
    assert(-1 == hmap->get(2), "Constructor [Bucket 2].");
    
    delete hmap;
}

void testPutNoCollision() {
    HashMap * hmap = new HashMap(3);

    hmap->put(0, 0);
    hmap->put(2, 2);

    assert(2 == hmap->getSize(), "PUT [size]     (no collision).");
    assert(0 == hmap->get(0),    "PUT [Bucket 0] (no collision).");
    assert(2 == hmap->get(2),    "PUT [Bucket 2] (no collision).");

    delete hmap;
}

void testPutCollision() {
    HashMap * hmap = new HashMap(3);

    hmap->put(0, 0);
    hmap->put(3, 3);

    assert(2 == hmap->getSize(),  "PUT [size]     (collision).");
    assert(0 == hmap->get(0),     "PUT [Bucket 0] (collision).");
    assert(3 == hmap->get(3),     "PUT [Bucket 0] (collision).");
    assert(-1 == hmap->get(6),    "PUT [Bucket 0] (collision).");

    delete hmap;
}

void testUpdateNoCollision() {
    HashMap * hmap = new HashMap(3);

    hmap->put(0, 0);
    hmap->put(0, 2);

    assert(1 == hmap->getSize(), "UPDATE [size]     (no collision).");
    assert(2 == hmap->get(0),    "UPDATE [Bucket 0] (no collision).");

    delete hmap;
}

void testUpdateCollision() {
    HashMap * hmap = new HashMap(3);

    hmap->put(0, 0);
    hmap->put(3, 3);
    hmap->put(3, 1);

    assert(2 == hmap->getSize(), "UPDATE [size]     (collision).");
    assert(0 == hmap->get(0),    "UPDATE [Bucket 0] (collision).");
    assert(1 == hmap->get(3),    "UPDATE [Bucket 0] (collision).");

    delete hmap;
}

void testRemoveNoCollision() {
    HashMap * hmap = new HashMap(3);

    hmap->put(0, 0);
    hmap->put(1, 1);
    hmap->remove(0);

    assert(1 == hmap->getSize(), "REMOVE [size]     (no collision).");
    assert(-1 == hmap->get(0),   "REMOVE [Bucket 0] (no collision).");
    assert(1 == hmap->get(1),    "REMOVE [Bucket 1] (no collision).");

    delete hmap;
}

void testRemoveCollisionHead() {
    HashMap * hmap = new HashMap(3);

    hmap->put(0, 0);
    hmap->put(3, 3);
    hmap->put(6, 6);
    hmap->remove(0);

    assert(2 == hmap->getSize(), "REMOVE [size]     (collision head).");
    assert(-1 == hmap->get(0),   "REMOVE [Bucket 0] (collision head).");
    assert(3 == hmap->get(3),    "REMOVE [Bucket 0] (collision head).");
    assert(6 == hmap->get(6),    "REMOVE [Bucket 0] (collision head).");

    delete hmap;
}
