#include "MoveBehaviour_AI.h"
#include "MapMovableElement.h"
#include "MapCollideMgr.h"
#include "support\CCPointExtension.h"
#include "MapTank.h"

USING_NS_CC;

void MoveBehaviour_AI::update( MapMovableElement *elem, float dt )
{
    static float elaps = 0.f;
    elaps += dt;

    if (elaps > 1.f)
    {
        elaps = 0.f;
        if (rand() % 3 == 1)
        {
            ((MapTank*)elem)->fire();
        }
    }

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
    MapElemVec collideElems = collideMgr->getCollideElem(aabb, 3.f);

    if (elem->isBlock(collideElems))
    {
        while (true)
        {
            eDirection change_dir = eDirection::random();
            if (change_dir != dir)
            {
                elem->setDirection(change_dir);
                break;
            }
        }
    }
    else
    {
        elem->setPosition(pos);

        elem->collide(collideElems);
    }
}

MoveBehaviour_AI * MoveBehaviour_AI::create()
{
    MoveBehaviour_AI *ret = new MoveBehaviour_AI;
    if (ret)
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}
