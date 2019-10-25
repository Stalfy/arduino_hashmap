#include "hashmap.h"

/**
 * The HashMap requires two template classes.
 * Key Hash contains the function that will be used to select the bucket to store into.
 * Key Comparator contains the function that allows the code to retrieve your key.
 * Both must be templated to the type that will be used for the keys.
 */
class Hash : public KeyHash<byte> {
    public:
        uint32_t operator() (byte key) {
            return key;
        }
};

class Comp : public KeyComparator<byte> {
    public:
        bool operator() (byte keyA, byte keyB) {
            return keyA == keyB;
        }
};

// The recommended number of buckets is a prime greater than 1.3 times
// the number of entries.
HashMap<byte, String, Hash, Comp>* hmap = new HashMap<byte, String, Hash, Comp>(5);

byte incomingByte = 0;

void setup() {
    // Ascii characters for 1, 2 and 3 repespectively.
    hmap->put(0x31, "I am string #1");
    hmap->put(0x32, "I am string #2");
    hmap->put(0x33, "I am string #3");

    Serial.begin(9600);
    Serial.println("Enter a number from 1 to 3. Others will not appear from the map.");
}

void loop() {
    if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();

        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte, HEX);

        String v;
        if(hmap->get(incomingByte, &v)) {
            Serial.println(v);
        }
    } 
}
