#include "MapAnimation.h"
#include "json\json.h"
#include "2d\CCAnimation.h"
#include "2d\CCSpriteFrameCache.h"
#include "base\CCVector.h"
#include "CCFileUtils.h"

namespace gouki {
    MapAnimation* s_pSharedMapAnimation = NULL;

    MapAnimation* MapAnimation::sharedMapAnimation( void ) {
        if (! s_pSharedMapAnimation) {
            s_pSharedMapAnimation = new MapAnimation();
            s_pSharedMapAnimation->init();
        }

        return s_pSharedMapAnimation;
    }

    void MapAnimation::purgeSharedMapAnimation( void ) {
        CC_SAFE_RELEASE_NULL(s_pSharedMapAnimation);
    }

    cocos2d::Animation * MapAnimation::createAnimation( const std::string &animName, const std::string &animSubName ) {
        Json::Value &jAnim = (*m_root)[animName];
        Json::Value &jSubAnim = jAnim[animSubName];
        if (!jSubAnim.isNull()) {
            Json::Value &jFrames = jSubAnim["frames"];
            auto frameArr = cocos2d::Vector<cocos2d::SpriteFrame*>(jFrames.size());
            for (Json::Value::ArrayIndex i = 0; i < jFrames.size(); ++i) {
                if (cocos2d::SpriteFrame *frame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(jFrames[i].asString())) {
                    frameArr.pushBack(frame);
                }
            }

            float delayPerUnit = 1.f / jSubAnim["rate"].asDouble();

            return cocos2d::Animation::createWithSpriteFrames(frameArr, delayPerUnit);
        }

        return nullptr;
    }

    void MapAnimation::init() {
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("main.plist", "main.png");

        auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile("animation.json");

        Json::Reader reader;
        m_root = new Json::Value;
        const char *beginDoc = (const char*)(fileData.getBytes());
        const char *endDoc = (const char*)(fileData.getBytes() + fileData.getSize());

        if (!reader.parse(beginDoc, endDoc, *m_root)) {
            cocos2d::MessageBox(reader.getFormatedErrorMessages().c_str(), "Json Parse Error!");
        }

        fileData.clear();
    }
}
