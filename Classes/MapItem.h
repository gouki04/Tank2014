#ifndef MapItem_h__
#define MapItem_h__

#include "MapElement.h"

class MapItem : public MapElement
{
public:
    virtual bool init();

    virtual eMapElement getElemType() { return eMapElement::Item; }
    virtual std::string getElemTypeStr() { return "Item"; }

    virtual bool isBlock() const { return false; }
};

#endif // MapItem_h__
