#include "MapElementFactory.h"
#include "MapBrick.h"
#include "MapSteel.h"
#include "MapGrass.h"
#include "MapWall.h"
#include "MapEnemyTank.h"
#include "support\CCPointExtension.h"
#include "MapUserTank.h"
#include "MapBase.h"
#include "MapBullet.h"

USING_NS_CC;

MapElement * MapElementFactory::createElem( const eMapElement &elemtype )
{
    if (elemtype == eMapElement::Brick)
    {
        return MapBrick::create();
    }
    else if (elemtype == eMapElement::Steel)
    {
        return MapSteel::create();
    }
    else if (elemtype == eMapElement::Grass)
    {
        return MapGrass::create();
    }
    else if (elemtype == eMapElement::Wall)
    {
        return MapWall::create();
    }
    else
    {
        return 0;
    }

    return 0;
}

MapTank * MapElementFactory::createEnemyTank( int level )
{
    MapEnemyTank *tank = MapEnemyTank::createWithLevel(level);
    tank->setAnchorPoint(ccp(0.5f, 0.5f));
    tank->setSpeed(80);
    tank->setDirection(eDirection::Down);
    
    return tank;
}

MapTank * MapElementFactory::createUserTank( int userId )
{
    MapUserTank *tank = MapUserTank::create();
    tank->setAnchorPoint(ccp(0.5f, 0.5f));
    tank->setSpeed(100);
    tank->setDirection(eDirection::Up);
    
    return tank;
}

MapElement * MapElementFactory::createBase()
{
    MapBase *base = MapBase::create();
    return base;
}

MapBullet * MapElementFactory::createBullet( MapTank *parent )
{
    MapBullet *bullet = MapBullet::create();
    bullet->setAnchorPoint(ccp(0.5f, 0.5f));
    bullet->setSpeed(200);
    
    return bullet;
}
