#ifndef BLOCK_H
#define BLOCK_H
#include <QTimer>

#include "gameitem.h"

class block:public GameItem
{
public:
    block(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BLOCK_H
