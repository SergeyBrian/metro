#ifndef METRO_STATIONLIST_H
#define METRO_STATIONLIST_H

#include <map>

#include "Station.h"


class StationList {
public:
    StationList();
    Station *getStation(station_id id);

private:
    std::map<station_id, Station *> stationsList;
};

#endif //METRO_STATIONLIST_H
