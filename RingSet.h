#pragma once

#include <cstdint>

// Store the numbers in the ring (position-independent)
// 2bits per value (16 bits total) - counter from 0 to 3 for count of value
// value mapping - 8877665544332211
typedef uint16_t RingSet;

const RingSet RINGSET_SOLVED = 0x5555;

void insert(RingSet& set, char value);
void remove(RingSet& set, char value);
bool solved(RingSet set);