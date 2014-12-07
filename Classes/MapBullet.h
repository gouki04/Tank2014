#ifndef MapBullet_h__
#define MapBullet_h__

#include "MapMovableElement.h"

namespace gouki {
    class MapTank;

    class MapBullet : public MapMovableElement
    {
    public:
        MapBullet();
        virtual ~MapBullet();

        virtual bool init() override;

        virtual void setSourceTank(MapTank *tank);
        virtual MapTank *getSourceTank() const { return m_sourceTank; }

        static MapBullet *create();

        virtual eMapElement getElemType() override { return eMapElement::Bullet; }
        virtual std::string getElemTypeStr() override { return "Bullet"; }

        virtual void collide(const MapElemVec &elems) override;

    protected:
        MapTank *m_sourceTank;
    };
}

#endif // MapBullet_h__
