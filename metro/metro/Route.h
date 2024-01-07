#ifndef METRO_ROUTE_H
#define METRO_ROUTE_H

#include "Utils.h"
#include "Station.h"
#include "search/Search.h"

/*
 * Как считать эвристическую функцию:
 * 1. Если ветка не совпадает с той, на которой целевая станция, + 1000 к функции
 * 2. Если с ветки есть пересадка на нужную ветку, - 100
 * 3. Если станция находится на нужной ветке, -1000
 * 4. Прибавляем расстояние от станции до целевой
 */

namespace metro {
    class Route {
        std::vector<Station *> target_stations;
        std::vector<Station *> route;

        bool stupidSearch();

    public:
        Route();

        std::vector<Station *> getRoute();

        std::vector<Station *> getTargetStations();

        void addStation(Station *station);

        void removeStation(Station *station);

        bool calculate(RouteSearchMethod method);

        void clear();
    };
}

#endif //METRO_ROUTE_H
