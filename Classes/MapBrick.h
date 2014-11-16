#ifndef MapBrick_h__
#define MapBrick_h__

#include "MapElement.h"

class MapBrick : public MapElement
{
public:
    MapBrick();
    ~MapBrick();

    virtual bool init();

    static MapBrick *create();

    virtual eMapElement getElemType() { return eMapElement::Brick; }
    virtual std::string getElemTypeStr() { return "Brick"; }

    virtual bool isBlock() const { return true; }
};

#endif // MapBrick_h__
