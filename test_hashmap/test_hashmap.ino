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

class H : public KeyHash<int> {
    public:
        uint32_t operator() (int key) {
            return key;
        }
};

class C : public KeyComparator<int> {
    public:
        bool operator() (int keyA, int keyB) {
            return keyA == keyB;
        }
};

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
    testRemoveCollisionBody();
    testRemoveCollisionTail();

    testIntToString();
    testIntToFunctor();
    testIntToFuncPtr();
    Serial.println("End test sequence.");    
}

void loop() {}

void testConstructor() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    assert(0 == hmap->getSize(), "Constructor default size.");
    assert(3 == hmap->getBuckets(), "Constructor buckets.");

    int v = 0;
    assert(false == hmap->get(0, &v), "Constructor [Bucket 0].");
    assert(false == hmap->get(1, &v), "Constructor [Bucket 1].");
    assert(false == hmap->get(2, &v), "Constructor [Bucket 2].");

    delete hmap;
}

void testPutNoCollision() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(2, 2);

    assert(2 == hmap->getSize(), "PUT [size]     (no collision).");

    int v;
    assert(true == hmap->get(0, &v),    "PUT [Bucket 0] (no collision).");
    assert(0 == v,                      "PUT [Bucket 0] (no collision).");
    assert(true == hmap->get(2, &v),    "PUT [Bucket 2] (no collision).");
    assert(2 == v,                      "PUT [Bucket 2] (no collision).");

    delete hmap;
}

void testPutCollision() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(3, 3);

    assert(2 == hmap->getSize(),  "PUT [size]     (collision).");

    int v;
    assert(true == hmap->get(0, &v),  "PUT [Bucket 0] (collision).");
    assert(0 == v,                    "PUT [Bucket 0] (collision).");
    assert(true == hmap->get(3, &v),  "PUT [Bucket 0] (collision).");
    assert(3 == v,                    "PUT [Bucket 0] (collision).");
    assert(false == hmap->get(6, &v), "PUT [Bucket 0] (collision).");
    assert(3 == v,                    "PUT [Bucket 0] (collision).");

    delete hmap;
}

void testUpdateNoCollision() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(0, 2);

    assert(1 == hmap->getSize(), "UPDATE [size]     (no collision).");

    int v;
    assert(true == hmap->get(0, &v), "UPDATE [Bucket 0] (no collision).");
    assert(2 == v,                   "UPDATE [Bucket 0] (no collision).");

    delete hmap;
}

void testUpdateCollision() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(3, 3);
    hmap->put(3, 1);

    assert(2 == hmap->getSize(), "UPDATE [size]     (collision).");

    int v;
    assert(true == hmap->get(0, &v), "UPDATE [Bucket 0] (collision).");
    assert(true == hmap->get(3, &v), "UPDATE [Bucket 0] (collision).");
    assert(1 == v,                   "UPDATE [Bucket 0] (collision).");

    delete hmap;
}

void testRemoveNoCollision() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(1, 1);
    hmap->remove(0);

    assert(1 == hmap->getSize(), "REMOVE [size]     (no collision).");

    int v;
    assert(false == hmap->get(0, &v), "REMOVE [Bucket 0] (no collision).");
    assert(true == hmap->get(1, &v),  "REMOVE [Bucket 1] (no collision).");

    delete hmap;
}

void testRemoveCollisionHead() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(3, 3);
    hmap->put(6, 6);
    hmap->remove(0);

    assert(2 == hmap->getSize(), "REMOVE [size]     (collision head).");

    int v;
    assert(false == hmap->get(0, &v),   "REMOVE [Bucket 0] (collision head).");
    assert(true == hmap->get(3, &v),    "REMOVE [Bucket 0] (collision head).");
    assert(true == hmap->get(6, &v),    "REMOVE [Bucket 0] (collision head).");

    delete hmap;
}

void testRemoveCollisionBody() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(3, 3);
    hmap->put(6, 6);
    hmap->remove(3);

    assert(2 == hmap->getSize(), "REMOVE [size]     (collision body).");

    int v;
    assert(true == hmap->get(0, &v),    "REMOVE [Bucket 0] (collision body).");
    assert(false == hmap->get(3, &v),   "REMOVE [Bucket 0] (collision body).");
    assert(true == hmap->get(6, &v),    "REMOVE [Bucket 0] (collision body).");

    delete hmap;
}

void testRemoveCollisionTail() {
    HashMap<int, int, H, C>* hmap = new HashMap<int, int, H, C>(3);

    hmap->put(0, 0);
    hmap->put(3, 3);
    hmap->put(6, 6);
    hmap->remove(6);

    assert(2 == hmap->getSize(), "REMOVE [size]     (collision tail).");

    int v;
    assert(true == hmap->get(0, &v),    "REMOVE [Bucket 0] (collision tail).");
    assert(true == hmap->get(3, &v),    "REMOVE [Bucket 0] (collision tail).");
    assert(false == hmap->get(6, &v),   "REMOVE [Bucket 0] (collision tail).");

    delete hmap;
}

void testIntToString() {
    HashMap<int, String, H, C>* hmap = new HashMap<int, String, H, C>(3);

    String expected = "The test string";
    hmap->put(0, expected);
    
    String v;
    assert(true == hmap->get(0, &v), "INT to STRING mapping.");
    assert(expected.equals(v),       "INT to STRING mapping.");

    expected = "The update";
    hmap->put(0, "The update");
    assert(true == hmap->get(0, &v), "INT to STRING mapping.");
    assert(expected.equals(v),       "INT to STRING mapping.");

    delete hmap;
}

void testIntToFunctor() {
    class TestFunctor {
        public:
            virtual bool operator() () = 0;
    };

    class TrueFunctor : public TestFunctor {
        public:
            ~TrueFunctor() {
                Serial.println("I true ded");
            }

            bool operator() () {
                return true;
            }
    };

    class FalseFunctor : public TestFunctor {
        public:
            ~FalseFunctor() {
                Serial.println("I false ded");
            }

            bool operator() () {
                return false;
            }
    };

    HashMap<int, TestFunctor*, H, C>* hmap = new HashMap<int, TestFunctor*, H, C>(3);
    hmap->put(0, new TrueFunctor());

    TestFunctor* v;
    assert(true == hmap->get(0, &v), "INT to FUNCTOR mapping.");
    assert(true == v->operator()(),  "INT to FUNCTOR mapping."); 
    
    hmap->put(0, new FalseFunctor());
    assert(true == hmap->get(0, &v), "INT to FUNCTOR mapping.");
    assert(false == v->operator()(), "INT to FUNCTOR mapping."); 
    
    delete hmap;
}

typedef int (*pfunc)();
int pfuncInsert() {
    return 1;
}

int pfuncUpdate() {
    return 2;
}

void testIntToFuncPtr() {
    HashMap<int, pfunc, H, C>* hmap = new HashMap<int, pfunc, H, C>(3);
    hmap->put(0, pfuncInsert);

    pfunc v;
    assert(true == hmap->get(0, &v), "INT to FUNC_PTR mapping insert.");
    assert(1 == v(),                 "INT to FUNC_PTR mapping insert.");
    
    hmap->put(0, pfuncUpdate);
    assert(true == hmap->get(0, &v), "INT to FUNC_PTR mapping update.");
    assert(2 == v(),                 "INT to FUNC_PTR mapping update.");
    
    delete hmap;
}
