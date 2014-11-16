#include "MapElementFactory.h"
#include "MapBrick.h"
#include "MapSteel.h"
#include "MapGrass.h"
#include "MapWall.h"

USING_NS_CC;

MapElement * MapElementFactory::create( const eMapElement &elemtype )
{
    if (elemtype == eMapElement::Brick)
    {
        return MapBrick::create();
    }
    else if (elemtype == eMapElement::Steel)
    {
        return MapSteel::create();
    }
    else if (elemtype == eMapElement::Grass)
    {
        return MapGrass::create();
    }
    else if (elemtype == eMapElement::Wall)
    {
        return MapWall::create();
    }
    else
    {
        return 0;
    }

    return 0;
}
