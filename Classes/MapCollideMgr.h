#ifndef MapCollideMgr_h__
#define MapCollideMgr_h__

#include "cocoa\CCObject.h"
#include "MapCommon.h"
#include <vector>
#include "cocoa\CCGeometry.h"
#include "Map.h"

class Map;

class MapCollideMgr : public cocos2d::CCObject
{
public:
    MapCollideMgr();
    ~MapCollideMgr();

    void setMap(Map *map);

    MapElemVec getCollideElemByMap(MapElement *elem, const cocos2d::CCRect &aabb);
    MapElemVec getBlockElemByMap(MapElement *elem, const cocos2d::CCRect &aabb);
    
    bool isBlock(MapElement *elem);
    bool isBlock(const cocos2d::CCRect &aabb);

    bool isHit(MapElement *elem, const cocos2d::CCRect &aabb);
    bool isHit(MapElement *elem, const cocos2d::CCRect &aabb, MapTankVec &tanks);

    MapElemVec getCollideElem(const cocos2d::CCRect &aabb, float allowance = 0.f);

    bool blockCheck(MapElement *elem, const cocos2d::CCRect &aabb);

public:
    static MapCollideMgr *sharedMapCollideMgr();
    static void purgeSharedMapCollideMgr();

protected:
    Map *m_map;
};

#endif // MapCollideMgr_h__
