#include "MapElementFactory.h"
#include "MapBrick.h"
#include "MapSteel.h"
#include "MapGrass.h"
#include "MapWall.h"
#include "MapEnemyTank.h"
#include "MapUserTank.h"
#include "MapBase.h"
#include "MapBullet.h"
#include "math\Vec2.h"

namespace gouki {
    MapElement * MapElementFactory::createElem( const eMapElement &elemtype )
    {
        if (elemtype == eMapElement::Brick) {
            return MapBrick::create();
        } else if (elemtype == eMapElement::Steel) {
            return MapSteel::create();
        } else if (elemtype == eMapElement::Grass) {
            return MapGrass::create();
        } else if (elemtype == eMapElement::Wall) {
            return MapWall::create();
        } else {
            return 0;
        }

        return 0;
    }

    MapTank * MapElementFactory::createEnemyTank( int level ) {
        auto tank = MapEnemyTank::createWithLevel(level);
        tank->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        tank->setSpeed(80);
        tank->setDirection(eDirection::Down);

        return tank;
    }

    MapTank * MapElementFactory::createUserTank( int userId ) {
        auto tank = MapUserTank::create();
        tank->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        tank->setSpeed(100);
        tank->setDirection(eDirection::Up);

        return tank;
    }

    MapElement * MapElementFactory::createBase() {
        auto base = MapBase::create();
        return base;
    }

    MapBullet * MapElementFactory::createBullet( MapTank *parent ) {
        auto bullet = MapBullet::create();
        bullet->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        bullet->setSpeed(200);

        return bullet;
    }
}
