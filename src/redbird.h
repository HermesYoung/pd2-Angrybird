#ifndef REDBIRD_H
#define REDBIRD_H
#include "gameitem.h"
#include "bird.h"

class redBird:public Bird
{
public:

    redBird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
virtual void ability();

};

#endif // REDBIRD_H
