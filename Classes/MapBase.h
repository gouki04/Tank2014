#ifndef MapBase_h__
#define MapBase_h__

#include "MapElement.h"

class MapBase : public MapElement
{
public:
    MapBase();
    virtual ~MapBase();

    virtual bool init();

    static MapBase *create();

    virtual eMapElement getElemType() { return eMapElement::Base; }
    virtual std::string getElemTypeStr() { return "MapBase"; }

    virtual bool isBlock() const { return true; }
};

#endif // MapBase_h__
