#ifndef METRO_SEARCH_H
#define METRO_SEARCH_H

#include "StupidSearcher.h"
#include "Exceptions.h"

namespace metro {
    enum RouteSearchMethod {
        STUPID,
        ROUTE_SEARCH_METHOD_COUNT
    };

    ISearcher *getSearcher(RouteSearchMethod method);

    extern const std::string search_method_name[ROUTE_SEARCH_METHOD_COUNT];
}

#endif //METRO_SEARCH_H
