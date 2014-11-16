#include "MapUserTank.h"
#include "MoveBehaviour_AI.h"
#include "MoveBehaviour_Keyboard.h"

USING_NS_CC;

MapUserTank::MapUserTank()
{
    m_animName = "UserTank_1";
}

MapUserTank::~MapUserTank()
{

}

bool MapUserTank::init()
{
    setMoveBahaviour(MoveBehaviour_Keyboard::create());
    playAnimation("idle");

    return true;
}

MapUserTank * MapUserTank::create()
{
    MapUserTank *ret = new MapUserTank;
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}

void MapUserTank::draw()
{
    MapTank::draw();


}
