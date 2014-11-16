#ifndef MapTank_h__
#define MapTank_h__

#include "MapMovableElement.h"

class IFireBehaviour;

class MapTank : public MapMovableElement
{
public:
    MapTank();

    virtual bool init();

    virtual void update(float dt);

    virtual bool isBlock(const MapElemVec &elems);
    virtual void collide(const MapElemVec &elems);

    virtual void setFireBehaviour(IFireBehaviour *behaviour);

    virtual void fire();

protected:
    IFireBehaviour *m_fireBehaviour;
};

#endif // MapTank_h__
