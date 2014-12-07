#ifndef MapWall_h__
#define MapWall_h__

#include "MapElement.h"

namespace gouki {
    class MapWall : public MapElement
    {
    public:
        MapWall();
        virtual ~MapWall();

        virtual bool init() override;

        static MapWall *create();

        virtual eMapElement getElemType() override { return eMapElement::Wall; }
        virtual std::string getElemTypeStr() override { return "Wall"; }

        virtual bool isBlock() const override { return true; }
    };
}

#endif // MapWall_h__
