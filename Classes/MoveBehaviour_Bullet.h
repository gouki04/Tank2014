#ifndef MoveBehaviour_Bullet_h__
#define MoveBehaviour_Bullet_h__

#include "IMoveBehaviour.h"

namespace gouki {
    class MoveBehaviour_Bullet : public IMoveBehaviour
    {
    public:
        virtual void update(MapMovableElement *elem, float dt);

        static MoveBehaviour_Bullet *create();
    };
}

#endif // MoveBehaviour_Bullet_h__
