#ifndef METRO_ASTARSEARCHER_H
#define METRO_ASTARSEARCHER_H

#include <unordered_map>

#include "ISearcher.h"
#include "Exceptions.h"
#include "../Utils.h"

namespace metro {
    class AStarSearcher : public ISearcher {
        Station *begin;
        Station *target;

        virtual int heuristicCost(Station *a);

        std::unordered_map<int, bool> visited;

        bool AStarAlg(std::vector<Station *> *route);

    public:
        bool findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route,
                               bool *stop = nullptr) override;

        ~AStarSearcher() override;
    };

    struct Vertex {
        Station *s;
        int g;
        int h;
        Vertex *parent;

        Vertex(Station *s, int g, int h, Vertex *parent);
    };
}

#endif //METRO_ASTARSEARCHER_H
