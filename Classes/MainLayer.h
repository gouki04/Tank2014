#ifndef MainLayer_h__
#define MainLayer_h__

#include "layers_scenes_transitions_nodes\CCLayer.h"

class Map;

class MainLayer : public cocos2d::CCLayer
{
public:
    MainLayer();
    virtual ~MainLayer();

    virtual bool init();

    static MainLayer *create();

protected:
    Map *m_map;
};

#endif // MainLayer_h__
