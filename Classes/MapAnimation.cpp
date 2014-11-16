#include "MapAnimation.h"
#include "sprite_nodes\CCSprite.h"
#include "json\json.h"
#include "sprite_nodes\CCAnimation.h"
#include "platform\CCFileUtils.h"
#include "sprite_nodes\CCSpriteFrameCache.h"

USING_NS_CC;

MapAnimation* s_pSharedMapAnimation = NULL;

MapAnimation* MapAnimation::sharedMapAnimation( void )
{
    if (! s_pSharedMapAnimation)
    {
        s_pSharedMapAnimation = new MapAnimation();
        s_pSharedMapAnimation->init();
    }

    return s_pSharedMapAnimation;
}

void MapAnimation::purgeSharedMapAnimation( void )
{
    CC_SAFE_RELEASE_NULL(s_pSharedMapAnimation);
}

cocos2d::CCAnimation * MapAnimation::createAnimation( const std::string &animName, const std::string &animSubName )
{
    Json::Value &jAnim = (*m_root)[animName];
    Json::Value &jSubAnim = jAnim[animSubName];
    if (!jSubAnim.isNull())
    {
        Json::Value &jFrames = jSubAnim["frames"];
        CCArray *frameArr = CCArray::create(jFrames.size());
        for (Json::Value::ArrayIndex i = 0; i < jFrames.size(); ++i)
        {
            if (CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(jFrames[i].asCString()))
                frameArr->addObject(frame);
        }

        float delayPerUnit = 1.f / jSubAnim["rate"].asDouble();

        return CCAnimation::create(frameArr, delayPerUnit);
    }

    return 0;
}

void MapAnimation::init()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("main.plist", "main.png");

    unsigned char *file_buffer;
    unsigned long file_size;

    file_buffer = CCFileUtils::sharedFileUtils()->getFileData("animation.json", "r", &file_size);

    Json::Reader reader;
    m_root = new Json::Value;
    const char *beginDoc = (const char*)(file_buffer);
    const char *endDoc = (const char*)(file_buffer+file_size);

    if (!reader.parse(beginDoc, endDoc, *m_root))
    {
        CCMessageBox(reader.getFormatedErrorMessages().c_str(), "Json Parse Error!");
    }
}
