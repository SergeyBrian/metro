#ifndef METRO_ASTARSEARCHER_H
#define METRO_ASTARSEARCHER_H

#include <unordered_map>

#include "ISearcher.h"
#include "Exceptions.h"
#include "../Utils.h"

namespace metro {
    struct Vertex {
        Station *s;
        int g;
        int h;
        Vertex *parent;

        Vertex(Station *s, int g, int h, Vertex *parent);
    };

    class AStarSearcher : public ISearcher {
    protected:
        Station *begin;
        Station *target;

        virtual int heuristicCost(Station *a);

        std::unordered_map<int, bool> visited;

        bool AStarAlg(std::vector<Station *> *route);

        std::vector<Vertex *> vertexes;

    public:
        bool findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route,
                               bool *stop = nullptr) override;

        ~AStarSearcher() override;
    };
}

#endif //METRO_ASTARSEARCHER_H
