#include "Station.h"

namespace metro {
    void bindStations(Station *a, Station *b) {
        a->connections.push_back(b);
        b->connections.push_back(a);
    }
}
