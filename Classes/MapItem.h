#ifndef MapItem_h__
#define MapItem_h__

#include "MapElement.h"

namespace gouki {
    class MapItem : public MapElement
    {
    public:
        MapItem();
        virtual ~MapItem();

        virtual bool init() override;

        virtual eMapElement getElemType() override { return eMapElement::Item; }
        virtual std::string getElemTypeStr() override { return "Item"; }

        virtual bool isBlock() const override { return false; }
    };
}

#endif // MapItem_h__
