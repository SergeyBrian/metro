#include "Route.h"

Route::Route(station_id target) {
    valid = false;
    length = 0;
    this->target = target;
}

station_insert_status Route::addStation(station_id station) {
    if (std::count(path.begin(), path.end(), station)) return FAIL;
    path.push_back(station);
    length++;
    if (station == target) {
        valid = true;
        return ROUTE_COMPLETE;
    }
    return SUCCESS;
}

Route::Route(const Route *obj) {
    this->valid = obj->valid;
    this->length = obj->length;
    this->target = obj->target;
    for (int i = 0; i < length; i ++) {
        this->path.push_back(obj->path.at(i));
    }
}
