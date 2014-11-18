#ifndef MapElement_h__
#define MapElement_h__

#include "MapCommon.h"
#include "base_nodes\CCNode.h"
#include <string>

namespace cocos2d {
    class CCSprite;
}

class Map;

class MapElement : public cocos2d::CCNode
{
public:
    MapElement();
    virtual ~MapElement();

    virtual bool init() { return true; }

    virtual eMapLayerOrder getLayerOrder() { return eMapLayerOrder::Background; }

    virtual void setMap(Map *map) { m_map = map; }
    virtual Map *getMap() const { return m_map; }

    virtual eMapElement getElemType() = 0;
    virtual std::string getElemTypeStr() = 0;

    virtual bool isBlock() const { return false; }

    virtual bool isBlock(const MapElemVec &elems);
    virtual void collide(const MapElemVec &elems);

    virtual void playAnimation(const std::string &name, const std::string &animSubName);
    virtual void playAnimation(const std::string &subName);

    virtual void setMainAnimName(const std::string &animName);

    virtual cocos2d::CCRect boundingBox();

protected:
    Map *m_map;
    cocos2d::CCSprite *m_mainSpr;
    std::string m_animName;
};

#endif // MapElement_h__
