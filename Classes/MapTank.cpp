#include "MapTank.h"
#include "IFireBehaviour.h"
#include "MapBullet.h"
#include "support\CCPointExtension.h"
#include "Map.h"

USING_NS_CC;

MapTank::MapTank()
: m_fireBehaviour(0)
{

}

void MapTank::setFireBehaviour( IFireBehaviour *behaviour )
{
    CC_SAFE_RELEASE_NULL(m_fireBehaviour);

    m_fireBehaviour = behaviour;
    CC_SAFE_RETAIN(m_fireBehaviour);
}

void MapTank::update( float dt )
{
    MapMovableElement::update(dt);

    if (m_fireBehaviour)
    {
        m_fireBehaviour->update(this, dt);
    }
}

bool MapTank::init()
{
    return true;
}

bool MapTank::isBlock( const MapElemVec &elems )
{
    MapElemVec::const_iterator iter = elems.begin();
    for (; iter != elems.end(); ++iter)
    {
        MapElement *elem = *iter;
        if (elem == this)
        {
            continue;
        }

        eMapElement elemType = elem->getElemType();
        if (elemType == eMapElement::Brick || 
            elemType == eMapElement::Wall || 
            elemType == eMapElement::Steel ||
            elemType == eMapElement::UserTank ||
            elemType == eMapElement::EnemyTank ||
            elemType == eMapElement::Base)
        {
            return true;
        }
    }

    return false;
}

void MapTank::collide( const MapElemVec &elems )
{
    MapElemVec::const_iterator iter = elems.begin();
    for (; iter != elems.end(); ++iter)
    {
        MapElement *elem = *iter;
        if (elem == this)
        {
            continue;
        }

        eMapElement elemType = elem->getElemType();
        if (elemType == eMapElement::Bullet)
        {
            // bomb
        }
    }
}

void MapTank::fire()
{
    MapBullet *bullet = MapBullet::create();
    bullet->setAnchorPoint(ccp(0.5f, 0.5f));
    bullet->setSpeed(200);
    bullet->setDirection(getDirection());
    bullet->setSourceTank(this);

    eDirection dir = getDirection();
    CCPoint pos = getPosition();
    CCSize size = getContentSize();
    if (dir == eDirection::Left)
    {
        pos.x -= size.width/2.f;
    }
    else if (dir == eDirection::Right)
    {
        pos.x += size.width/2.f;
    }
    else if (dir == eDirection::Up)
    {
        pos.y += size.height/2.f;
    }
    else if (dir == eDirection::Down)
    {
        pos.y -= size.height/2.f;
    }
    
    bullet->setPosition(pos);

    m_map->addBullet(bullet);
}
