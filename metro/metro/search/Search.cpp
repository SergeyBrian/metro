#include "Search.h"

namespace metro {
    ISearcher *getSearcher(RouteSearchMethod method) {
        switch (method) {
            case STUPID:
                return new StupidSearcher();
                break;
        }
    }
}
