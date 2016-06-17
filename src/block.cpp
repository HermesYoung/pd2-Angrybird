#include "block.h"

block::block(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
g_pixmap.setPixmap(pixmap);
g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width() / 2, g_pixmap.boundingRect().height() / 2);
g_size=QSize(w,h);

b2BodyDef define;
define.active=true;
define.type=b2_dynamicBody;
define.bullet=true;
define.position.Set(x,y);
define.userData=this;
g_body=world->CreateBody(&define);

b2PolygonShape shape;
shape.SetAsBox(w/2,h/2);

b2FixtureDef fixture;
fixture.shape=&shape;
fixture.density=10.0f;
fixture.friction=0.2f;
fixture.restitution=0.5f;

g_body->SetAngularDamping(2);
g_body->CreateFixture(&fixture);

connect(timer,SIGNAL(timeout()),this,SLOT(paint()));
scene->addItem(&g_pixmap);
}
