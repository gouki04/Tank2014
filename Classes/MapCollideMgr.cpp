#include "MapCollideMgr.h"
#include "Map.h"
#include "MapElement.h"
#include <math.h>
#include "MapTank.h"
#include "MapBullet.h"

USING_NS_CC;

#define TERRAIN_ALLOWANCE 5.f

static MapCollideMgr *pSharedMapCollideMgr = NULL;

MapCollideMgr * MapCollideMgr::sharedMapCollideMgr()
{
    if (! pSharedMapCollideMgr)
    {
        pSharedMapCollideMgr = new MapCollideMgr();
        //pSharedMapCollideMgr->init();
    }

    return pSharedMapCollideMgr;
}

void MapCollideMgr::purgeSharedMapCollideMgr()
{
    CC_SAFE_RELEASE_NULL(pSharedMapCollideMgr);
}

MapCollideMgr::MapCollideMgr()
: m_map(0)
{

}

MapCollideMgr::~MapCollideMgr()
{
    CC_SAFE_RELEASE_NULL(m_map);
}

MapElemVec MapCollideMgr::getCollideElemByMap( MapElement *elem, const cocos2d::CCRect &aabb )
{
    int left = (int)floor(aabb.origin.x / MAP_ELEM_WIDTH);
    int right = (int)ceil((aabb.origin.x + aabb.size.width) / MAP_ELEM_WIDTH);
    int bottom = (int)floor(aabb.origin.y / MAP_ELEM_HEIGHT);
    int top = (int)ceil((aabb.origin.y + aabb.size.height) / MAP_ELEM_HEIGHT);

    MapElemVec ret;
    for (int r = bottom; r <= top; ++r)
    {
        for (int c = left; c <= right; ++c)
        {
            if (MapElement * elem = m_map->getElementAt(r, c))
            {
                ret.push_back(elem);
            }
        }
    }

    return ret;
}

MapElemVec MapCollideMgr::getBlockElemByMap( MapElement *elem, const cocos2d::CCRect &aabb )
{
    MapElemVec elems = getCollideElemByMap(elem, aabb);

    MapElemVec::iterator iter = elems.begin();
    for (; iter != elems.end(); )
    {
        if (!(*iter)->isBlock())
        {
            iter = elems.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    return elems;
}

bool MapCollideMgr::isBlock( MapElement *elem )
{
    return isBlock(elem->boundingBox());
}

bool MapCollideMgr::isBlock( const cocos2d::CCRect &aabb )
{
    int left = (int)floor((aabb.origin.x + TERRAIN_ALLOWANCE) / MAP_ELEM_WIDTH);
    int right = (int)floor((aabb.origin.x + aabb.size.width - TERRAIN_ALLOWANCE) / MAP_ELEM_WIDTH);
    int bottom = (int)floor((aabb.origin.y + TERRAIN_ALLOWANCE) / MAP_ELEM_HEIGHT);
    int top = (int)floor((aabb.origin.y + aabb.size.height - TERRAIN_ALLOWANCE) / MAP_ELEM_HEIGHT);

    if (left <= 0 || bottom <= 0)
    {
        return true;
    }

    if (top >= m_map->getRow() || right >= m_map->getCol())
    {
        return true;
    }

    for (int r = bottom; r <= top; ++r)
    {
        for (int c = left; c <= right; ++c)
        {
            if (MapElement * elem = m_map->getElementAt(r, c))
            {
                if (elem->isBlock())
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void MapCollideMgr::setMap( Map *map )
{
    CC_SAFE_RELEASE_NULL(m_map);

    m_map = map;
    CC_SAFE_RETAIN(m_map);
}

bool MapCollideMgr::isHit( MapElement *elem, const cocos2d::CCRect &aabb )
{
    MapTankVec &userTanks = m_map->getUserTanks();

    if (isHit(elem, aabb, userTanks))
    {
        return true;
    }
    else
    {
        return isHit(elem, aabb, m_map->getEnemyTanks());
    }
}

bool MapCollideMgr::isHit( MapElement *elem, const cocos2d::CCRect &aabb, MapTankVec &tanks )
{
    MapTankVec::iterator iter = tanks.begin();
    for (; iter != tanks.end(); ++iter)
    {
        MapTank *tank = *iter;
        if (elem == tank)
        {
            continue;
        }

        CCRect r = tank->boundingBox();
        if (CCRect::CCRectIntersectsRect(r, aabb))
        {
            return true;
        }
    }

    return false;
}

MapElemVec MapCollideMgr::getCollideElem( const cocos2d::CCRect &aabb, float allowance/* = 0.f*/ )
{
    int left = (int)floor((aabb.origin.x + allowance) / MAP_ELEM_WIDTH);
    int right = (int)floor((aabb.origin.x + aabb.size.width - allowance) / MAP_ELEM_WIDTH);
    int bottom = (int)floor((aabb.origin.y + allowance) / MAP_ELEM_HEIGHT);
    int top = (int)floor((aabb.origin.y + aabb.size.height - allowance) / MAP_ELEM_HEIGHT);

    if (left <= 0)
    {
        left = 0;
    }

    if (bottom <= 0)
    {
        bottom = 0;
    }

    if (top >= m_map->getRow())
    {
        top = m_map->getRow();
    }

    if (right >= m_map->getCol())
    {
        right = m_map->getCol();
    }

    MapElemVec ret;
    for (int r = bottom; r <= top; ++r)
    {
        for (int c = left; c <= right; ++c)
        {
            if (MapElement * elem = m_map->getElementAt(r, c))
            {
                ret.push_back(elem);
            }
        }
    }

    MapTankVec &userTanks = m_map->getUserTanks();
    MapTankVec::iterator iter1 = userTanks.begin();
    for (; iter1 != userTanks.end(); ++iter1)
    {
        MapTank *tank = *iter1;

        CCRect r = tank->boundingBox();
        if (CCRect::CCRectIntersectsRect(r, aabb))
        {
            ret.push_back(tank);
        }
    }

    MapTankVec &enemyTanks = m_map->getEnemyTanks();
    MapTankVec::iterator iter2 = enemyTanks.begin();
    for (; iter2 != enemyTanks.end(); ++iter2)
    {
        MapTank *tank = *iter2;

        CCRect r = tank->boundingBox();
        if (CCRect::CCRectIntersectsRect(r, aabb))
        {
            ret.push_back(tank);
        }
    }

    MapBulletVec &bullets = m_map->getBullets();
    MapBulletVec::iterator iter3 = bullets.begin();
    for (; iter3 != bullets.end(); ++iter3)
    {
        MapBullet *bullet = *iter3;

        CCRect r = bullet->boundingBox();
        if (CCRect::CCRectIntersectsRect(r, aabb))
        {
            ret.push_back(bullet);
        }
    }

    if (MapElement *base = m_map->getBase())
    {
        CCRect r = base->boundingBox();
        if (CCRect::CCRectIntersectsRect(r, aabb))
        {
            ret.push_back(base);
        }
    }

    return ret;
}

bool MapCollideMgr::blockCheck( MapElement *elem, const cocos2d::CCRect &aabb )
{
    return true;
}


