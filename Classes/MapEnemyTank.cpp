#include "MapEnemyTank.h"
#include "MoveBehaviour_AI.h"
#include "deprecated\CCString.h"

namespace gouki {
    MapEnemyTank::MapEnemyTank() {
        m_animName = "EnemyTank_1";
    }

    MapEnemyTank::~MapEnemyTank() {

    }

    bool MapEnemyTank::initWithLevel( int level ) {
        m_animName = cocos2d::StringUtils::format("EnemyTank_%d", level);

        setMoveBahaviour(MoveBehaviour_AI::create());
        playAnimation("idle");

        return true;
    }

    MapEnemyTank * MapEnemyTank::createWithLevel( int level ) {
        MapEnemyTank *ret = new MapEnemyTank;
        if (ret && ret->initWithLevel(level)) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return 0;
    }
}
