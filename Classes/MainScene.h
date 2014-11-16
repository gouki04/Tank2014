#ifndef MainScene_h__
#define MainScene_h__

#include "layers_scenes_transitions_nodes\CCScene.h"

class MainScene : public cocos2d::CCScene
{
public:
    MainScene();
    virtual ~MainScene();

    virtual void onEnter();

    static MainScene *create();
};

#endif // MainScene_h__
