#ifndef MovBehaviour_AI_h__
#define MovBehaviour_AI_h__

#include "IMoveBehaviour.h"

namespace gouki {
    class MoveBehaviour_AI : public IMoveBehaviour
    {
    public:
        virtual void update(MapMovableElement *elem, float dt);

        static MoveBehaviour_AI *create();
    };
}

#endif // MovBehaviour_AI_h__
