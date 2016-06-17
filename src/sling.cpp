#include "sling.h"

sling::sling(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(w-1.0, h+2.0);

    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.type=b2_staticBody;
    bodyDef.position.Set(x, y);
    g_body = world->CreateBody(&bodyDef);

    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w / 2, h / 2);
    g_body->CreateFixture(&bodyBox, 9.0f);

    scene->addItem(&g_pixmap);
    paint();
}
