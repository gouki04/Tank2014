#ifndef IFireBehaviour_h__
#define IFireBehaviour_h__

#include "cocoa\CCObject.h"

class MapTank;

class IFireBehaviour : public cocos2d::CCObject
{
public:
    virtual void update(MapTank *elem, float dt) = 0;
};

#endif // IFireBehaviour_h__
