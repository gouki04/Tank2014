#ifndef MapSteel_h__
#define MapSteel_h__

#include "MapElement.h"

namespace gouki {
    class MapSteel : public MapElement
    {
    public:
        MapSteel();
        virtual ~MapSteel();

        virtual bool init() override;

        static MapSteel *create();

        virtual eMapElement getElemType() override { return eMapElement::Steel; }
        virtual std::string getElemTypeStr() override { return "Steel"; }

        virtual bool isBlock() const override { return true; }
    };
}

#endif // MapSteel_h__
