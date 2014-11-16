#ifndef MapAnimation_h__
#define MapAnimation_h__

#include "cocoa/CCObject.h"
#include <string>

namespace cocos2d {
    class CCAnimation;
}

namespace Json {
    class Value;
}

class MapAnimation : public cocos2d::CCObject
{
public:
    static MapAnimation* sharedMapAnimation(void);

    static void purgeSharedMapAnimation(void);

    void init();

    cocos2d::CCAnimation *createAnimation(const std::string &animName, const std::string &animSubName);

private:
    Json::Value *m_root;
};

#endif // MapAnimation_h__
