#include "MoveBehaviour_Bullet.h"
#include "MapMovableElement.h"
#include "MapCollideMgr.h"
#include "support\CCPointExtension.h"

USING_NS_CC;

void MoveBehaviour_Bullet::update( MapMovableElement *elem, float dt )
{
    float move_dist = elem->getSpeed() * dt;
    CCRect aabb = elem->boundingBox();
    CCPoint pos = elem->getPosition();

    eDirection dir = elem->getDirection();
    if (dir == eDirection::Left)
    {
        pos.x -= move_dist;
        aabb.origin.x -= move_dist;
    }
    else if (dir == eDirection::Right)
    {
        pos.x += move_dist;
        aabb.origin.x += move_dist;
    }
    else if (dir == eDirection::Up)
    {
        pos.y += move_dist;
        aabb.origin.y += move_dist;
    }
    else
    {
        pos.y -= move_dist;
        aabb.origin.y -= move_dist;
    }

    MapCollideMgr *collideMgr = MapCollideMgr::sharedMapCollideMgr();
    MapElemVec collideElems = collideMgr->getCollideElem(aabb);

    elem->setPosition(pos);

    elem->collide(collideElems);
}

MoveBehaviour_Bullet * MoveBehaviour_Bullet::create()
{
    MoveBehaviour_Bullet *ret = new MoveBehaviour_Bullet;
    if (ret)
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}
