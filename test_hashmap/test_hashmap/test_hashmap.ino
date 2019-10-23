void setup() {
    Serial.begin(9600);

    Serial.println("Begin test sequence.");
    testConstructor();
    Serial.println("End test sequence.");    
}

void loop() {}

void testConstructor() {
    HashMap * hmap = new HashMap(3);
    
    if(0 == hmap.getSize()) {
        Serial.println("[PASS] Constructor default size test.");
    }

    if(3 == hmap.getBuckets()) {
        Serial.println("[PASS] Constructor buckets test.");
    }

    delete hmap;
}
