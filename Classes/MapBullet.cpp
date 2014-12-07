#include "MapBullet.h"
#include "MapTank.h"
#include "MoveBehaviour_Bullet.h"
#include "Map.h"

namespace gouki {
    MapBullet::MapBullet()
        : m_sourceTank(nullptr) {
        m_animName = "Bullet1";
    }

    MapBullet::~MapBullet() {
        CC_SAFE_RELEASE_NULL(m_sourceTank);
    }

    bool MapBullet::init() {
        setMoveBahaviour(MoveBehaviour_Bullet::create());
        playAnimation("idle");

        return true;
    }

    void MapBullet::setSourceTank( MapTank *tank ) {
        CC_SAFE_RELEASE_NULL(m_sourceTank);

        m_sourceTank = tank;
        CC_SAFE_RETAIN(m_sourceTank);
    }

    MapBullet * MapBullet::create() {
        MapBullet *ret = new MapBullet;
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return 0;
    }

    void MapBullet::collide( const MapElemVec &elems ) {
        bool selfBomb = false;

        MapElemVec::const_iterator iter = elems.begin();
        for (; iter != elems.end(); ++iter) {
            MapElement *elem = *iter;
            if (elem == this) {
                continue;
            }

            eMapElement elemType = elem->getElemType();
            if (elemType == eMapElement::Brick) {
                selfBomb = true;
                m_map->removeElement(elem);
            } else if (elemType == eMapElement::Wall || 
                elemType == eMapElement::Steel) {
                selfBomb = true;
            } else if (elemType == eMapElement::UserTank ||
                elemType == eMapElement::EnemyTank) {
                if (elem != m_sourceTank && elemType != m_sourceTank->getElemType()) {
                    selfBomb = true;

                    m_map->addBomb(elem->getPosition());
                    m_map->removeElement(elem);
                }
            } else if (elemType == eMapElement::Bullet) {
                selfBomb = true;

                m_map->addSmallBomb(elem->getPosition());
                m_map->removeElement(elem);
            } else if (elemType == eMapElement::Base) {
                selfBomb = true;

                m_map->addBomb(elem->getPosition());

                m_map->removeElement(elem);
                cocos2d::MessageBox("Game Over!!!", "Doby");
            }
        }

        if (selfBomb) {
            m_map->addSmallBomb(getPosition());
            m_map->removeElement(this);
        }
    }
}
