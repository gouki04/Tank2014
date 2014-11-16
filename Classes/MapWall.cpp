#include "MapWall.h"
#include "sprite_nodes\CCSprite.h"

USING_NS_CC;

bool MapWall::init()
{
    return true;
}

MapWall * MapWall::create()
{
    MapWall *ret = new MapWall;
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}
