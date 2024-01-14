#ifndef METRO_SEARCH_H
#define METRO_SEARCH_H

#include "StupidSearcher.h"
#include "AStarSearcher.h"
#include "AStarImproved.h"
#include "Exceptions.h"

namespace metro {
    enum RouteSearchMethod {
        STUPID,
        A_STAR,
        A_STAR_IMPROVED,
        ROUTE_SEARCH_METHOD_COUNT
    };

    ISearcher *getSearcher(RouteSearchMethod method);

    extern const std::string search_method_name[ROUTE_SEARCH_METHOD_COUNT];
}

#endif //METRO_SEARCH_H
