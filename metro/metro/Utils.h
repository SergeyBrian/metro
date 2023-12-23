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

    int distanceToLineSegment(const Position &p, const Position &a, const Position &b);

    float invSqrt(float number);

    double projectionParameter(const Position &point, const Position &lineStart, const Position &lineEnd);
}

#endif //METRO_UTILS_H
