#ifndef METRO_STATIONELLIPSE_H
#define METRO_STATIONELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "graphicsitemhelper.h"

#include "metro/Metro.h"

#define MARKER_SELECT_INDICATOR_WIDTH 5

class StationEllipse : public QGraphicsEllipseItem {
public:
    explicit StationEllipse(QRectF rect);

    void Station(metro::Station *s);

    metro::Station *Station();

    bool toggleSelect();

    GraphicsItemHelper *Helper();

    void addToScene(QGraphicsScene *scene);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    GraphicsItemHelper *helper;

private:
    void itemClicked(StationEllipse *stationMarker);

    QGraphicsEllipseItem *selectCircle;

    bool selected;

    metro::Station *station{};
};

#endif //METRO_STATIONELLIPSE_H
