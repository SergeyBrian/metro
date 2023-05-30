#ifndef STATIONBUTTON_H
#define STATIONBUTTON_H

#include "navigator/StationList.h"

class StationButton
{
public:
    StationButton(station_id id, int x, int y);
    station_id id;
    std::pair<int, int> coords;
};

#endif // STATIONBUTTON_H
