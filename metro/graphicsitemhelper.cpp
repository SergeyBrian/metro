#include "graphicsitemhelper.h"

void GraphicsItemHelper::emit_itemClicked(QGraphicsItem *item) {
    emit itemClicked(item);
}
