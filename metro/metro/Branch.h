#ifndef METRO_BRANCH_H
#define METRO_BRANCH_H

#include "Station.h"
#include "Color.h"

#define BRANCH_MASK 0xffff;

namespace metro {
    struct Branch {
        int id;
        int stations_count;
        Color color;
        Station *begin;
        Station *end;
    };
}

#endif //METRO_BRANCH_H
