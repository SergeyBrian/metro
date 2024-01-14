#include "AStarImproved.h"

int metro::AStarImprovedSearcher::heuristicCost(metro::Station *a) {
    int res = getDistanceSquared(a->pos, target->pos);
    if (a->branch_id == target->branch_id) res -= 1000;
    else
        for (const auto &station: a->connections) {
            if (station->branch_id == target->branch_id) res -= 500;
            break;
        }
    return res;
}
