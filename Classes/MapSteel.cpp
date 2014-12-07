#include "MapSteel.h"

namespace gouki {
    MapSteel::MapSteel() {
        m_animName = "Steel";
    }

    MapSteel::~MapSteel() {

    }

    bool MapSteel::init() {
        //initWithSprite("steel.png");
        playAnimation("idle");
        return true;
    }

    MapSteel * MapSteel::create() {
        MapSteel *ret = new MapSteel;
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
