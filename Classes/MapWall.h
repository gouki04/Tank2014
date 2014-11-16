#ifndef MapWall_h__
#define MapWall_h__

#include "MapElement.h"

class MapWall : public MapElement
{
public:
    virtual bool init();

    static MapWall *create();

    virtual eMapElement getElemType() { return eMapElement::Wall; }
    virtual std::string getElemTypeStr() { return "Wall"; }

    virtual bool isBlock() const { return true; }
};

#endif // MapWall_h__
