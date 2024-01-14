#include "Station.h"

namespace metro {
    void bindStations(Station *a, Station *b) {
        if (std::find(a->connections.begin(), a->connections.end(), b) == a->connections.end()) {
            a->connections.push_back(b);
        }
        if (std::find(b->connections.begin(), b->connections.end(), a) == b->connections.end()) {
            b->connections.push_back(a);
        }
    }
}
