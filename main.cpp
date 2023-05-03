#include <iostream>

#include "StationList.h"
#include "Navigator.h"

int main() {
    auto *stationList = new StationList();
    auto *navigator = new Navigator(stationList);

    auto *route = new std::vector<station_id>;
    int l = navigator->findShortestRoute(stationList->getStation(NARVSKAYA), stationList->getStation(ELEKTROSILA), nullptr, route);


    return 0;
}
