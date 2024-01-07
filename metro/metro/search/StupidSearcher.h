#ifndef METRO_STUPIDSEARCHER_H
#define METRO_STUPIDSEARCHER_H

#include "ISearcher.h"

#include "../Utils.h"

namespace metro {

    class StupidSearcher : public ISearcher {
        std::vector<std::vector<Station *>> allRoutes;

        void findAllRoutes(const std::vector<Station *> &targetStations, std::vector<Station *> curr_route);

        std::vector<Station *> selectShortestRoute();

    public:
        bool findShortestRoute(const std::vector<Station *> &targetStations, std::vector<Station *> *route) override;

        ~StupidSearcher() override;
    };

}

#endif //METRO_STUPIDSEARCHER_H
