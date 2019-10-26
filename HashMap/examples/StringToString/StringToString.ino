#include "hashmap.h"

/**
 * The HashMap requires two template classes.
 * Key Hash contains the function that will be used to select the bucket to store into.
 * Key Comparator contains the function that allows the code to retrieve your key.
 * Both must be templated to the type that will be used for the keys.
 */
class Hash : public KeyHash<String> {
    public:
        uint32_t operator() (String key) {
            // FNV-1a 32-bit hashing function.
            uint32_t hash = 0x811c9dc5;

            for(int i = 0; i < key.length(); i++) {
                hash ^= key.charAt(i);
                hash *= 0x01000193;
            }

            return hash;
        }
};

class Comp : public KeyComparator<String> {
    public:
        bool operator() (String keyA, String keyB) {
            return keyA.equals(keyB);
        }
};

// The recommended number of buckets is a prime greater than 1.3 times
// the number of entries.
HashMap<String, String, Hash, Comp>* hmap = new HashMap<String, String, Hash, Comp>(5);

byte incomingByte = 0;

void setup() {
    // Ascii characters for 1, 2 and 3 repespectively.
    hmap->put("str1", "I am string #1");
    hmap->put("str2", "I am string #2");

    Serial.begin(9600);
    Serial.println("Enter str1 or str2. Other inputs will not appear from the map.");
}

void loop() {
}

void serialEvent() {
    if (Serial.available() > 0) {
        // read the incoming byte:
        String line = Serial.readString();

        // Cut the final line feed character.
        line = line.substring(0, line.length() - 1);

        // say what you got:
        Serial.print("I received: ");
        Serial.println(line);

        String v;
        if(hmap->get(line, &v)) {
            Serial.println(v);
        }
    } 

}
