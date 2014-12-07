#ifndef MapElementFactory_h__
#define MapElementFactory_h__

#include "MapCommon.h"
#include "base\CCRef.h"

namespace gouki {
    class MapElement;
    class MapTank;
    class MapBullet;

    class MapElementFactory : public cocos2d::Ref
    {
    public:
        static MapElement *createElem(const eMapElement &elemtype);

        static MapTank *createEnemyTank(int level);

        static MapTank *createUserTank(int userId);

        static MapElement *createBase();

        static MapBullet *createBullet(MapTank *parent);
    };
}

#endif // MapElementFactory_h__
