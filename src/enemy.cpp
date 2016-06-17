#include "enemy.h"

enemy::enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(radius*2,radius*2);

    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;

    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = 10.0f;
    fixturedef.friction = 0.5f;
    fixturedef.restitution = 0.5f;
    g_body->SetAngularDamping(5);
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}
b2Vec2 enemy::positionCheck()
{
    return g_body->GetPosition();
}
b2Vec2 enemy::VelocityCheck()
{
    return g_body->GetLinearVelocity();
}
void enemy::killEnemy()
{
    isKilled=true;
    delete this;
}
