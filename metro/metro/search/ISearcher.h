#ifndef METRO_ISEARCHER_H
#define METRO_ISEARCHER_H

#include "../Station.h"
#include "../Branch.h"

namespace metro {
    class ISearcher {
    public:
        virtual bool findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route) = 0;

        virtual ~ISearcher();
    };
}

#endif //METRO_ISEARCHER_H
