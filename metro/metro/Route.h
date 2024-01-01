#ifndef METRO_ROUTE_H
#define METRO_ROUTE_H

#include "Utils.h"
#include "Station.h"

/*
 * Как считать эвристическую функцию:
 * 1. Если ветка не совпадает с той, на которой целевая станция, + 1000 к функции
 * 2. Если с ветки есть пересадка на нужную ветку, - 100
 * 3. Если станция находится на нужной ветке, -1000
 * 4. Прибавляем расстояние от станции до целевой
 */

namespace metro {
    enum RouteSearchMethod {
        DIJKSTRA,
    };

    struct Route {
        std::vector<Station *> target_stations;
        std::vector<Station *> route;
    };

    bool calculateRoute(Route *route, RouteSearchMethod method);
}

#endif //METRO_ROUTE_H
