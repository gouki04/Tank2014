#include "MapEnemyTank.h"
#include "MoveBehaviour_AI.h"
#include "StringUtility.h"

USING_NS_CC;

MapEnemyTank::MapEnemyTank()
{
    m_animName = "EnemyTank_1";
}

MapEnemyTank::~MapEnemyTank()
{

}

bool MapEnemyTank::initWithLevel( int level )
{
    setMoveBahaviour(MoveBehaviour_AI::create());
    playAnimation("idle");

    return true;
}

MapEnemyTank * MapEnemyTank::createWithLevel( int level )
{
    MapEnemyTank *ret = new MapEnemyTank;
    if (ret && ret->initWithLevel(level))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return 0;
}
