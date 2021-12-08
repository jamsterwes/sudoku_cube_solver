#include "Options.h"
#include "RingSet.h"
#include <cassert>

void insert(RingSet& set, char value)
{
#ifdef DEBUG_INSERT
    assert((set >> ((value - 1) * 2) & 0x3) != 0x3);
#endif
    set += 1 << ((value - 1) * 2);
}

void remove(RingSet& set, char value)
{
#ifdef DEBUG_INSERT
    assert((set >> ((value - 1) * 2) & 0x3) != 0x0);
#endif
    set -= 1 << ((value - 1) * 2);
}

bool solved(RingSet set)
{
    return set == RINGSET_SOLVED;
}