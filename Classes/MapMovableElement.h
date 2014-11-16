#ifndef MapMovableElement_h__
#define MapMovableElement_h__

#include "MapElement.h"
#include <map>
#include <string>

namespace cocos2d
{
    class CCSprite;
}

class IMoveBehaviour;

class MapMovableElement : public MapElement
{
public:
    MapMovableElement();
    ~MapMovableElement();

    virtual bool init();

    virtual void onEnter();
    virtual void onExit();

    virtual void setDirection(const eDirection &dir);
    virtual eDirection getDirection() const { return m_direction; }
    virtual bool isDirection(const eDirection &dir) { return m_direction == dir; }

    virtual void setSpeed(float speed) { m_speed = speed; }
    virtual float getSpeed() const { return m_speed; }

    virtual void setIsMoving(bool moving) { m_isMoving = moving; }
    virtual bool getIsMoving() const { return m_isMoving; }

    virtual void update(float dt);

protected:
    virtual void setMoveBahaviour(IMoveBehaviour *behaviour);

protected:
    IMoveBehaviour *m_moveBahaviour;
    eDirection m_direction;
    float m_speed;

    bool m_isMoving;
};

#endif // MapMovableElement_h__
