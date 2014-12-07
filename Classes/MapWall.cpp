#include "MapWall.h"

namespace gouki {
    MapWall::MapWall() {

    }

    MapWall::~MapWall() {

    }

    bool MapWall::init() {
        return true;
    }

    MapWall * MapWall::create() {
        MapWall *ret = new MapWall;
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }

        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}
