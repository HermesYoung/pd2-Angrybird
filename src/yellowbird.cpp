#include "yellowbird.h"

yellowbird::yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void yellowbird::ability()
{
    this->setLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x*2000, g_body->GetLinearVelocity().y*2000));
}
