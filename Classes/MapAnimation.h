#ifndef MapAnimation_h__
#define MapAnimation_h__

#include <string>
#include "base/CCRef.h"

namespace cocos2d {
    class Animation;
}

namespace Json {
    class Value;
}

namespace gouki {
    class MapAnimation : public cocos2d::Ref
    {
    public:
        static MapAnimation* sharedMapAnimation(void);

        static void purgeSharedMapAnimation(void);

        void init();

        cocos2d::Animation *createAnimation(const std::string &animName, const std::string &animSubName);

    private:
        Json::Value *m_root;
    };
}

#endif // MapAnimation_h__
