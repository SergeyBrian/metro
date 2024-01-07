#include "Search.h"

namespace metro {
    ISearcher *getSearcher(RouteSearchMethod method) {
        switch (method) {
            case STUPID:
                return new StupidSearcher();
            default:
                throw InvalidSearchMethodException();
        }
    }

    const std::string search_method_name[]{
            "Stupid search",
    };
}