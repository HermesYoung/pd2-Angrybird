#include "whitebird.h"

whitebird::whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void whitebird::ability()
{
    this->setLinearVelocity(b2Vec2(0,-200));
}
