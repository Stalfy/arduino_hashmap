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

// Start by defining the mapped function.
typedef void (*mappedFn)();

// Then define its possible implementations.
// These can be implemented now or after your main code.
// It will be implemented after in this example.
void blinkSlowly();
void blinkQuickly();

// The recommended number of buckets is a prime greater than 1.3 times
// the number of entries.
HashMap<byte, mappedFn, Hash, Comp>* hmap = new HashMap<byte, mappedFn, Hash, Comp>(5);

byte incomingByte = 0;
uint32_t blinkDelay = 1000;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    // Ascii characters for 1 and 2 repespectively.
    hmap->put(0x31, blinkSlowly);
    hmap->put(0x32, blinkQuickly);

    Serial.begin(9600);
    Serial.println("Enter a number from 1 to 2. Other signals shall be ignored.");
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(blinkDelay);
    digitalWrite(LED_BUILTIN, LOW);
    delay(blinkDelay);
}

void serialEvent() {
    while(Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();

        // say what you got:
        Serial.print("I received: ");
        Serial.println(incomingByte, HEX);

        mappedFn fn;
        if(hmap->get(incomingByte, &fn)) {
            fn();
        }
    } 
}

// Implementation of the previously declared methods.
void blinkSlowly() {
    Serial.println("I shall blink slowly.");
    blinkDelay = 1000;
}

void blinkQuickly() {
    Serial.println("I shall blink quickly.");
    blinkDelay = 200;
}
