#ifndef MapElementFactory_h__
#define MapElementFactory_h__

#include "cocoa\CCObject.h"
#include "MapCommon.h"

class MapElement;

class MapElementFactory : public cocos2d::CCObject
{
public:
    static MapElement *create(const eMapElement &elemtype);
};

#endif // MapElementFactory_h__
