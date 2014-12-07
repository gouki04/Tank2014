#include "MapMovableElement.h"
#include "IMoveBehaviour.h"

namespace gouki {
    MapMovableElement::MapMovableElement()
        : m_direction(eDirection::Up)
        , m_moveBahaviour(0)
        , m_isMoving(false) {

    }

    MapMovableElement::~MapMovableElement() {
        CC_SAFE_RELEASE_NULL(m_moveBahaviour);
    }

    void MapMovableElement::setMoveBahaviour( IMoveBehaviour *behaviour ) {
        CC_SAFE_RELEASE_NULL(m_moveBahaviour);

        m_moveBahaviour = behaviour;
        CC_SAFE_RETAIN(m_moveBahaviour);
    }

    void MapMovableElement::update( float dt ) {
        if (m_moveBahaviour) {
            m_moveBahaviour->update(this, dt);
        }
    }

    void MapMovableElement::setDirection( const eDirection &dir ) {
        m_direction = dir;

        std::string animName;
        if (m_isMoving) {
            animName = "move";
        } else {
            animName = "idle";
        }

        if (dir == eDirection::Down) {
            animName += "D";
            //setRotation(180);
        } else if (dir == eDirection::Up) {
            animName += "U";
            //setRotation(0);
        } else if (dir == eDirection::Left) {
            animName += "L";
            //setRotation(-90);
        } else if (dir == eDirection::Right) {
            animName += "R";
            //setRotation(90);
        }

        playAnimation(animName);
    }

    void MapMovableElement::onEnter() {
        MapElement::onEnter();

        scheduleUpdate();
    }

    void MapMovableElement::onExit() {
        MapElement::onExit();

        unscheduleUpdate();
    }

    bool MapMovableElement::init() {
        return true;
    }
}
