#ifndef METRO_NAVIGATOR_H
#define METRO_NAVIGATOR_H

#include <vector>
#include <algorithm>

#include "StationList.h"

class Navigator {
public:
    Navigator(StationList *stationList);
    int findShortestRoute(Station *start, Station *end, Station *prev, std::vector<station_id> *route);
private:
    StationList *stationList;
};


#endif //METRO_NAVIGATOR_H
