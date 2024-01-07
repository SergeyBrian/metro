#ifndef METRO_SEARCH_H
#define METRO_SEARCH_H

#include "StupidSearcher.h"

namespace metro {
    enum RouteSearchMethod {
        STUPID,
    };

    ISearcher *getSearcher(RouteSearchMethod method);

}

#endif //METRO_SEARCH_H
