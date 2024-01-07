#ifndef METRO_STUPIDSEARCHER_H
#define METRO_STUPIDSEARCHER_H

#include "ISearcher.h"

namespace metro {

    class StupidSearcher : public ISearcher {
    public:
        bool findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route) override;

        ~StupidSearcher() override;
    };

}

#endif //METRO_STUPIDSEARCHER_H
