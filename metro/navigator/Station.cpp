#include "Station.h"

Station::Station(std::string name, station_id id) {
    this->name = name;
    this->id = id;
}

void Station::Connect(Station *station) {
    connections.push_back(station->id);
    station->connections.push_back(this->id);
}
