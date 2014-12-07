#ifndef MapTank_h__
#define MapTank_h__

#include "MapMovableElement.h"

namespace gouki {
    class IFireBehaviour;

    class MapTank : public MapMovableElement
    {
    public:
        MapTank();
        virtual ~MapTank();

        virtual bool init() override;

        virtual void update(float dt) override;

        virtual bool isBlock(const MapElemVec &elems) override;
        virtual void collide(const MapElemVec &elems) override;

        virtual void setFireBehaviour(IFireBehaviour *behaviour);

        virtual void fire();

    protected:
        IFireBehaviour *m_fireBehaviour;
    };
}

#endif // MapTank_h__
