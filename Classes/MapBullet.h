#ifndef MapBullet_h__
#define MapBullet_h__

#include "MapMovableElement.h"

class MapTank;

class MapBullet : public MapMovableElement
{
public:
    MapBullet();
    virtual ~MapBullet();

    virtual bool init();

    virtual void setSourceTank(MapTank *tank);
    virtual MapTank *getSourceTank() const { return m_sourceTank; }

    static MapBullet *create();

    virtual eMapElement getElemType() { return eMapElement::Bullet; }
    virtual std::string getElemTypeStr() { return "Bullet"; }

    virtual void collide(const MapElemVec &elems);

protected:
    MapTank *m_sourceTank;
};

#endif // MapBullet_h__
