#ifndef IFireBehaviour_h__
#define IFireBehaviour_h__

#include "base\CCRef.h"

namespace gouki {
    class MapTank;

    class IFireBehaviour : public cocos2d::Ref
    {
    public:
        virtual void update(MapTank *elem, float dt) = 0;
    };
}

#endif // IFireBehaviour_h__
