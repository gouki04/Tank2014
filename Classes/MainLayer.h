#ifndef MainLayer_h__
#define MainLayer_h__

#include "cocos\2d\CCLayer.h"

namespace gouki {
    class Map;

    class MainLayer : public cocos2d::Layer 
    {
    public:
        MainLayer();
        virtual ~MainLayer();

        virtual bool init();

        static MainLayer *create();

    protected:
        Map *m_map;
    };
}

#endif // MainLayer_h__
