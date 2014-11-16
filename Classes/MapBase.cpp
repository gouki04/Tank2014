#include "MapBase.h"
#include "sprite_nodes\CCSprite.h"

USING_NS_CC;

MapBase::MapBase()
{
    m_animName = "Base";
}

MapBase::~MapBase()
{

}

bool MapBase::init()
{
    playAnimation("idle");
    return true;
}

MapBase * MapBase::create()
{
    MapBase *ret = new MapBase;
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}
