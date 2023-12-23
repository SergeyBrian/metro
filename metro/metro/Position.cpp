#include "Position.h"

metro::Position metro::operator-(const metro::Position &a, const metro::Position &b) {
    return {a.x - b.x, a.y - b.y};
}

metro::Position metro::operator+(const metro::Position &a, const metro::Position &b) {
    return {a.x + b.x, a.y + b.y};
}
