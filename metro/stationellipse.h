#ifndef METRO_STATIONELLIPSE_H
#define METRO_STATIONELLIPSE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

#include "graphicsitemhelper.h"

#include "metro/Metro.h"

#define MARKER_SELECT_INDICATOR_WIDTH 5

class StationEllipse : public QGraphicsEllipseItem {
    metro::Station *station{};
public:
    explicit StationEllipse(QRectF rect);

    void Station(metro::Station *s);

    metro::Station *Station();

    void toggleSelect();

    GraphicsItemHelper *Helper();

    void addToScene(QGraphicsScene *scene);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    GraphicsItemHelper *helper;

private:
    void itemClicked(StationEllipse *stationMarker);

    QGraphicsEllipseItem *selectCircle;

    bool selected;
};

#endif //METRO_STATIONELLIPSE_H
