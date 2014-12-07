#ifndef IMoveBehaviour_h__
#define IMoveBehaviour_h__

#include "base\CCRef.h"

namespace gouki {
    class MapMovableElement;

    class IMoveBehaviour : public cocos2d::Ref
    {
    public:
        virtual void update(MapMovableElement *elem, float dt) = 0;
    };
}

#endif // IMoveBehaviour_h__
