#ifndef MapBase_h__
#define MapBase_h__

#include "MapElement.h"

namespace gouki {
    class MapBase : public MapElement
    {
    public:
        MapBase();
        virtual ~MapBase();

        virtual bool init() override;

        static MapBase *create();

        virtual eMapElement getElemType() override { return eMapElement::Base; }
        virtual std::string getElemTypeStr() override { return "MapBase"; }

        virtual bool isBlock() const override { return true; }
    };
}

#endif // MapBase_h__
