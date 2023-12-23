#include "stationellipse.h"

void StationEllipse::Station(metro::Station *s) {
    station = s;
}

metro::Station *StationEllipse::Station() {
    return station;
}

void StationEllipse::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    helper->emit_itemClicked(dynamic_cast<QGraphicsItem *>(this));
}

StationEllipse::StationEllipse() {
    helper = new GraphicsItemHelper(this);
}

