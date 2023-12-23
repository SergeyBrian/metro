#ifndef METRO_POSITION_H
#define METRO_POSITION_H

namespace metro {
    struct Position {
        int x;
        int y;
    };

    Position operator-(const Position &a, const Position &b);

    Position operator+(const Position &a, const Position &b);
}

#endif //METRO_POSITION_H
