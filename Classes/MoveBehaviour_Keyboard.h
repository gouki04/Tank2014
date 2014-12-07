#ifndef MoveBehaviour_Keyboard_h__
#define MoveBehaviour_Keyboard_h__

#include "IMoveBehaviour.h"

namespace gouki {
    class MoveBehaviour_Keyboard : public IMoveBehaviour
    {
    public:
        virtual void update(MapMovableElement *elem, float dt);

        static MoveBehaviour_Keyboard *create();
    };
}

#endif // MoveBehaviour_Keyboard_h__
