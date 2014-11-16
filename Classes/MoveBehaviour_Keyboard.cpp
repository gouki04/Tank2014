#include "MoveBehaviour_Keyboard.h"
#include "MapMovableElement.h"
#include "MapCollideMgr.h"
#include "support\CCPointExtension.h"
#include "MapTank.h"
#include "KeyBoardMgr.h"

USING_NS_CC;

void MoveBehaviour_Keyboard::update( MapMovableElement *elem, float dt )
{
    static float elaps = 0;
    elaps += dt;

    KeyBoardMgr *keyboardMgr = KeyBoardMgr::sharedKeyBoardMgr();

    eDirection dir = eDirection::Invalid;
    if (keyboardMgr->isKeyDown('A'))
    {
        dir = eDirection::Left;
    }
    else if (keyboardMgr->isKeyDown('D'))
    {
        dir = eDirection::Right;
    }
    else if (keyboardMgr->isKeyDown('W'))
    {
        dir = eDirection::Up;
    }
    else if (keyboardMgr->isKeyDown('S'))
    {
        dir = eDirection::Down;
    }
    else if (keyboardMgr->isKeyDown('F'))
    {
        if (elaps > 1.f)
        {
            ((MapTank*)elem)->fire();
            elaps = 0.f;
        }
    }

    if (dir == eDirection::Invalid)
    {
        return;
    }

    float move_dist = elem->getSpeed() * dt;
    CCRect aabb = elem->boundingBox();
    
    CCPoint pos = elem->getPosition();

    if (elem->getDirection() != dir)
    {
        elem->setDirection(dir);
        return;
    }

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
        return;
    }
    else
    {
        elem->setPosition(pos);

        elem->collide(collideElems);
    }
}

MoveBehaviour_Keyboard * MoveBehaviour_Keyboard::create()
{
    MoveBehaviour_Keyboard *ret = new MoveBehaviour_Keyboard;
    if (ret)
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}
