#ifndef MapCollideMgr_h__
#define MapCollideMgr_h__

#include "MapCommon.h"
#include <vector>
#include "Map.h"
#include "base\CCRef.h"

namespace gouki {
    class Map;

    class MapCollideMgr : public cocos2d::Ref
    {
    public:
        MapCollideMgr();
        virtual ~MapCollideMgr();

        void setMap(Map *map);

        MapElemVec getCollideElemByMap(MapElement *elem, const cocos2d::Rect &aabb);
        MapElemVec getBlockElemByMap(MapElement *elem, const cocos2d::Rect &aabb);

        bool isBlock(MapElement *elem);
        bool isBlock(const cocos2d::Rect &aabb);

        bool isHit(MapElement *elem, const cocos2d::Rect &aabb);
        bool isHit(MapElement *elem, const cocos2d::Rect &aabb, MapTankVec &tanks);

        MapElemVec getCollideElem(const cocos2d::Rect &aabb, float allowance = 0.f);

        bool blockCheck(MapElement *elem, const cocos2d::Rect &aabb);

    public:
        static MapCollideMgr *sharedMapCollideMgr();
        static void purgeSharedMapCollideMgr();

    protected:
        Map *m_map;
    };
}

#endif // MapCollideMgr_h__
