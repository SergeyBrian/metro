#ifndef METRO_UTILS_H
#define METRO_UTILS_H

#include <random>

#include "Position.h"

namespace metro {
    int randint(int min, int max);

    int biasedRandomInt(int min, int max);

    bool chance(float chance);

    int getDistanceSquared(const Position &a, const Position &b);

    bool isInOppositeQuadrant(const Position &a, const Position &b, const Position &center);
}

#endif //METRO_UTILS_H
