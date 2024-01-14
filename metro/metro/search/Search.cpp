#include "Search.h"

namespace metro {
    ISearcher *getSearcher(RouteSearchMethod method) {
        switch (method) {
            case STUPID:
                return new StupidSearcher();
            case A_STAR:
                return new AStarSearcher();
            case A_STAR_IMPROVED:
                return new AStarImprovedSearcher();
            case MOSCOW_STAR:
                return new MoscowStarSearcher();
            default:
                throw InvalidSearchMethodException();
        }
    }

    const std::string search_method_name[]{
            "Stupid search",
            "A* search",
            "A* improved search",
            "Moscow* search",
    };
}
