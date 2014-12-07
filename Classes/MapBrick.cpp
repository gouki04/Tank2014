#include "MapBrick.h"

namespace gouki {
    MapBrick::MapBrick() {
        m_animName = "Brick";
    }

    MapBrick::~MapBrick() {

    }

    bool MapBrick::init() {
        playAnimation("idle");
        return true;
    }

    MapBrick * MapBrick::create() {
        MapBrick *ret = new MapBrick;
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
