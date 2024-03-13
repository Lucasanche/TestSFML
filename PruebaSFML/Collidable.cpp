#include "Collidable.h"

bool Collidable::isCollision(Collidable& obj) const
{
    return getBounds().intersects(obj.getBounds());
}
