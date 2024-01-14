#include "graphicsscene.h"

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton) return;
    QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
    auto ell = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
    if (!ell) return;
    
}
