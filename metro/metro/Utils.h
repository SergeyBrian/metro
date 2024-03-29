#ifndef METRO_UTILS_H
#define METRO_UTILS_H

#include <random>

#include "Position.h"

namespace metro {
    int randint(int min, int max);

    int biasedRandomInt(int min, int max);

    bool chance(float chance);

    int getDistanceSquared(const Position &a, const Position &b);

    int getDistance(const Position &a, const Position &b);

    bool isInOppositeQuadrant(const Position &a, const Position &b, const Position &center);

    int distanceToLineSegment(const Position &p, const Position &a, const Position &b);

    float invSqrt(float number);

    double projectionParameter(const Position &point, const Position &lineStart, const Position &lineEnd);

    int squareRadius(const Position &center, const Position &point);

    Position getLineSegmentsIntersection(const Position &a1, const Position &b1,
                                         const Position &a2, const Position &b2);

    Position avgPos(const Position &a, const Position &b);
}

#endif //METRO_UTILS_H
