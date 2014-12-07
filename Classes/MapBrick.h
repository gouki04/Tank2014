#ifndef MapBrick_h__
#define MapBrick_h__

#include "MapElement.h"

namespace gouki {
    class MapBrick : public MapElement
    {
    public:
        MapBrick();
        virtual ~MapBrick();

        virtual bool init() override;

        static MapBrick *create();

        virtual eMapElement getElemType() override { return eMapElement::Brick; }
        virtual std::string getElemTypeStr() override { return "Brick"; }

        virtual bool isBlock() const override { return true; }
    };
}

#endif // MapBrick_h__
