#ifndef KEYCOMPARATOR_H_
#define KEYCOMPARATOR_H_

#include "Arduino.h"

template <typename K>
class KeyComparator {
    public:
        KeyComparator() {};
        virtual bool operator() (K keyA, K keyB) = 0;
};

#endif
