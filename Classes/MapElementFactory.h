#ifndef MapElementFactory_h__
#define MapElementFactory_h__

#include "cocoa\CCObject.h"
#include "MapCommon.h"

class MapElement;
class MapTank;
class MapBullet;

class MapElementFactory : public cocos2d::CCObject
{
public:
    static MapElement *createElem(const eMapElement &elemtype);

    static MapTank *createEnemyTank(int level);

    static MapTank *createUserTank(int userId);

    static MapElement *createBase();

    static MapBullet *createBullet(MapTank *parent);
};

#endif // MapElementFactory_h__
