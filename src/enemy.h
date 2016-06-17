#ifndef ENEMY_H
#define ENEMY_H
#include "gameitem.h"

#include <QTimer>

class enemy:public GameItem
{
public:
    enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    b2Vec2 positionCheck();
    b2Vec2 VelocityCheck();
    bool isKilled=false;
    void killEnemy();
};

#endif // ENEMY_H
