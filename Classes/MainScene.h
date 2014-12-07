#ifndef MainScene_h__
#define MainScene_h__

#include "cocos\2d\CCScene.h"

namespace gouki {
    class MainScene : public cocos2d::Scene
    {
    public:
        MainScene();
        virtual ~MainScene();

        virtual void onEnter();

        static MainScene *create();
    };
}

#endif // MainScene_h__
