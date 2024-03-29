#include "Utils.h"

namespace metro {
    int randint(int min, int max) {
        return min + (rand() % static_cast<int>(max - min + 1));
    }

    bool chance(float chance) {
        if (chance >= 1) return true;
        if (chance <= 0) return false;

        int x = (int) (1.0 / chance);
        return rand() % x == 0;
    }

    int biasedRandomInt(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        int num_samples = 3;

        int sum = 0;
        for (int i = 0; i < num_samples; ++i) {
            sum += dis(gen);
        }

        return sum / num_samples;
    }

    int getDistanceSquared(const Position &a, const Position &b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return dx * dx + dy * dy;
    }

    int getDistance(const Position &a, const Position &b) {
        return static_cast<int>(std::sqrt(getDistanceSquared(a, b)));
    }

    bool isInOppositeQuadrant(const Position &a, const Position &b, const Position &center) {
        Position a_prime = a - center;
        Position b_prime = b - center;

        // Check if a_prime and b_prime are in opposite quadrants
        // They are in opposite quadrants if one of the following is true:
        // - a_prime.x and b_prime.x have different signs AND a_prime.y and b_prime.y have different signs
        return (a_prime.x * b_prime.x <= 0) && (a_prime.y * b_prime.y <= 0);
    }

    int distanceToLineSegment(const Position &p, const Position &a, const Position &b) {
        int A = (b.y - a.y) * p.x - (b.x - a.x) * p.y + b.x * a.y - b.y * a.x;
        int B = (b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x);
        return static_cast<int>(static_cast<float>(abs(A)) * invSqrt(static_cast<float>(B)));
    }

    float invSqrt(float number) {
#ifdef METRO_USE_C_INV_SQRT_ALG
        union {
            float f;
            uint32_t i;
        } conv;

        float x2;
        const float threehalfs = 1.5F;

        x2 = number * 0.5F;
        conv.f = number;
        conv.i = 0x5f3759df - (conv.i >> 1);
        conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
        return conv.f;
#else
        return 1 / std::sqrt(number);
#endif
    }

    int squareRadius(const Position &center, const Position &point) {
        return (center.x - point.x) * (center.x - point.x) + (center.y - point.y) * (center.y - point.y);
    }

    Position avgPos(const Position &a, const Position &b) {
        return {
                .x = (a.x + b.x) / 2,
                .y = (a.y + b.y) / 2,
        };
    }

    Position getLineSegmentsIntersection(const Position &a1, const Position &b1,
                                         const Position &a2, const Position &b2) {
        float n;
        if (b1.y - a1.y != 0) {
            float q = static_cast<float>(b1.x - a1.x) / static_cast<float>(a1.y - b1.y);
            float sn = static_cast<float>(a2.x - b2.x) + static_cast<float>(a2.y - b2.y) * q;
            if (sn == 0) return {.x = -1, .y = -1};
            float fn = static_cast<float>(a2.x - a1.x) + static_cast<float>(a2.y - a1.y) * q;
            n = fn / sn;
        } else {
            if (!(a2.y - b2.y)) return {.x = -1, .y = -1};
            n = static_cast<float>(a2.y - a1.y) / static_cast<float>(a2.y - b2.y);
        }

        Position result = {
                .x = a2.x + static_cast<int>(static_cast<float>(b2.x - a2.x) * n),
                .y = a2.y + static_cast<int>(static_cast<float>(b2.y - a2.y) * n),
        };

        if (((result.x > a1.x && result.x < b1.x) || (result.x < a1.x && result.x > b1.x)) &&
            ((result.y > a1.y && result.y < b1.y) || (result.y < a1.y && result.y > b1.y)))
            return result;

        return {.x = -1,
                .y = -1
        };
    }
}

