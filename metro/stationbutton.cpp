#include "stationbutton.h"

StationButton::StationButton(station_id id, int x, int y)
{
    this->id = id;
    this->coords.first = x;
    this->coords.second = y;
}
