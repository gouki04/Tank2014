#include "MapTank.h"
#include "IFireBehaviour.h"
#include "MapBullet.h"
#include "Map.h"

namespace gouki {
    MapTank::MapTank()
        : m_fireBehaviour(0) {

    }

    MapTank::~MapTank() {

    }

    void MapTank::setFireBehaviour( IFireBehaviour *behaviour ) {
        CC_SAFE_RELEASE_NULL(m_fireBehaviour);

        m_fireBehaviour = behaviour;
        CC_SAFE_RETAIN(m_fireBehaviour);
    }

    void MapTank::update( float dt ) {
        MapMovableElement::update(dt);

        if (m_fireBehaviour) {
            m_fireBehaviour->update(this, dt);
        }
    }

    bool MapTank::init() {
        return true;
    }

    bool MapTank::isBlock( const MapElemVec &elems ) {
        auto iter = elems.begin();
        for (; iter != elems.end(); ++iter) {
            MapElement *elem = *iter;
            if (elem == this) {
                continue;
            }

            eMapElement elemType = elem->getElemType();
            if (elemType == eMapElement::Brick || 
                elemType == eMapElement::Wall || 
                elemType == eMapElement::Steel ||
                elemType == eMapElement::UserTank ||
                elemType == eMapElement::EnemyTank ||
                elemType == eMapElement::Base) {
                return true;
            }
        }

        return false;
    }

    void MapTank::collide( const MapElemVec &elems ) {
        auto iter = elems.begin();
        for (; iter != elems.end(); ++iter) {
            MapElement *elem = *iter;
            if (elem == this) {
                continue;
            }

            eMapElement elemType = elem->getElemType();
            if (elemType == eMapElement::Bullet) {
                // bomb
            }
        }
    }

    void MapTank::fire() {
        auto bullet = MapBullet::create();
        bullet->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        bullet->setSpeed(200);
        bullet->setDirection(getDirection());
        bullet->setSourceTank(this);

        eDirection dir = getDirection();
        cocos2d::Vec2 pos = getPosition();
        cocos2d::Size size = getContentSize();

        if (dir == eDirection::Left) {
            pos.x -= size.width/2.f;
        } else if (dir == eDirection::Right) {
            pos.x += size.width/2.f;
        } else if (dir == eDirection::Up) {
            pos.y += size.height/2.f;
        } else if (dir == eDirection::Down) {
            pos.y -= size.height/2.f;
        }

        bullet->setPosition(pos);

        m_map->addBullet(bullet);
    }
}
