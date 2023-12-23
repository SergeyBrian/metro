#ifndef METRO_GRAPHICSITEMHELPER_H
#define METRO_GRAPHICSITEMHELPER_H

#include <QObject>
#include <QGraphicsItem>

class GraphicsItemHelper : public QObject {
Q_OBJECT

public:
    GraphicsItemHelper(QGraphicsItem *parent) : QObject() {}

    void emit_itemClicked(QGraphicsItem *item);

signals:

    void itemClicked(QGraphicsItem *item);
};

#endif //METRO_GRAPHICSITEMHELPER_H
