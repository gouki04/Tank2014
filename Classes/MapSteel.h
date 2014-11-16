#ifndef MapSteel_h__
#define MapSteel_h__

#include "MapElement.h"

class MapSteel : public MapElement
{
public:
    MapSteel();
    ~MapSteel();

    virtual bool init();

    static MapSteel *create();

    virtual eMapElement getElemType() { return eMapElement::Steel; }
    virtual std::string getElemTypeStr() { return "Steel"; }

    virtual bool isBlock() const { return true; }
};

#endif // MapSteel_h__
