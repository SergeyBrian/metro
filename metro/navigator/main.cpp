#include <iostream>

#include "Navigator.h"

int main() {
    auto *stationList = new StationList();
    auto *navigator = new Navigator(stationList);
    Route *route = navigator->findShortestRoute(BALTIYSKAYA, VASILEOSTROVSKAYA);
    stationList->printRoute(route);
    return 0;
}
