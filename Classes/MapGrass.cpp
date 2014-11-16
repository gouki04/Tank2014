#include "MapGrass.h"
#include "sprite_nodes\CCSprite.h"

USING_NS_CC;

MapGrass::MapGrass()
{
    m_animName = "Grass";
}

MapGrass::~MapGrass()
{

}

bool MapGrass::init()
{
    //initWithSprite("grass.png");
    playAnimation("idle");
    return true;
}

MapGrass * MapGrass::create()
{
    MapGrass *ret = new MapGrass;
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}
