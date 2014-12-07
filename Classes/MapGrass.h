#ifndef MapGrass_h__
#define MapGrass_h__

#include "MapElement.h"

namespace gouki {
    class MapGrass : public MapElement
    {
    public:
        MapGrass();
        virtual ~MapGrass();

        virtual bool init() override;

        static MapGrass *create();

        virtual eMapElement getElemType() override { return eMapElement::Grass; }
        virtual std::string getElemTypeStr() override { return "Grass"; }
    };
}

#endif // MapGrass_h__
