#ifndef MapElement_h__
#define MapElement_h__

#include "MapCommon.h"
#include <string>
#include "2d\CCNode.h"

namespace cocos2d {
    class Sprite;
}

namespace gouki {
    class Map;

    class MapElement : public cocos2d::Node
    {
    public:
        MapElement();
        virtual ~MapElement();

        virtual bool init() override { return true; }

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

        virtual cocos2d::Rect getBoundingBox() const override;

    protected:
        Map *m_map;
        cocos2d::Sprite *m_mainSpr;
        std::string m_animName;
    };
}

#endif // MapElement_h__
