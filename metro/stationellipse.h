#ifndef METRO_STATIONELLIPSE_H
#define METRO_STATIONELLIPSE_H

#include <QGraphicsEllipseItem>

#include "graphicsitemhelper.h"

#include "metro/Metro.h"

class StationEllipse : public QGraphicsEllipseItem {
    metro::Station *station{};
public:
    StationEllipse();

    void Station(metro::Station *s);

    metro::Station *Station();

    GraphicsItemHelper *helper;


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void itemClicked(StationEllipse *stationMarker);
};

#endif //METRO_STATIONELLIPSE_H
