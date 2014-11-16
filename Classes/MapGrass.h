#ifndef MapGrass_h__
#define MapGrass_h__

#include "MapElement.h"

class MapGrass : public MapElement
{
public:
    MapGrass();
    ~MapGrass();

    virtual bool init();

    static MapGrass *create();

    virtual eMapElement getElemType() { return eMapElement::Grass; }
    virtual std::string getElemTypeStr() { return "Grass"; }
};

#endif // MapGrass_h__
