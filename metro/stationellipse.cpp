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

StationEllipse::StationEllipse(QRectF rect) {
    helper = new GraphicsItemHelper(this);
    selected = false;
    this->setRect(rect);
    selectCircle = new QGraphicsEllipseItem();
    selectCircle->setPen({Qt::red});
    selectCircle->setRect(
            {this->rect().x() - MARKER_SELECT_INDICATOR_WIDTH / 2,
             this->rect().y() - MARKER_SELECT_INDICATOR_WIDTH / 2,
             this->rect().width() + MARKER_SELECT_INDICATOR_WIDTH,
             this->rect().height() + MARKER_SELECT_INDICATOR_WIDTH});
    selectCircle->setVisible(false);
}

void StationEllipse::toggleSelect() {
    selected = !selected;
    selectCircle->setVisible(selected);
}

GraphicsItemHelper *StationEllipse::Helper() {
    return helper;
}

void StationEllipse::addToScene(QGraphicsScene *scene) {
    scene->addItem(this);
    scene->addItem(selectCircle);
}

