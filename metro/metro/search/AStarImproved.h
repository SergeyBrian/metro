#ifndef METRO_ASTARIMPROVED_H
#define METRO_ASTARIMPROVED_H

#include "AStarSearcher.h"

namespace metro {
    class AStarImprovedSearcher : public AStarSearcher {
    private:
        int heuristicCost(Station *a) override;
    };
}

#endif //METRO_ASTARIMPROVED_H
