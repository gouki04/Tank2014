#ifndef IMoveBehaviour_h__
#define IMoveBehaviour_h__

#include "cocoa\CCObject.h"

class MapMovableElement;

class IMoveBehaviour : public cocos2d::CCObject
{
public:
    virtual void update(MapMovableElement *elem, float dt) = 0;
};

#endif // IMoveBehaviour_h__
