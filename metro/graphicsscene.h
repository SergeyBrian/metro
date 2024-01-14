#ifndef METRO_GRAPHICSSCENE_H
#define METRO_GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "stationellipse.h"

class GraphicsScene : public QGraphicsScene {
Q_OBJECT

public:
    explicit GraphicsScene(QObject *parent = nullptr) : QGraphicsScene(parent) {};
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif //METRO_GRAPHICSSCENE_H
