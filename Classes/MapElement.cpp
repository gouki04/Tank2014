#include "MapElement.h"
#include "sprite_nodes\CCSprite.h"
#include "support\CCPointExtension.h"
#include "MapAnimation.h"
#include "actions/CCActionInterval.h"

USING_NS_CC;

#define MAP_ELEM_ANIM_TAG 99

MapElement::MapElement()
: m_mainSpr(0)
{

}

MapElement::~MapElement()
{

}

void MapElement::initWithSprite( const char *filename )
{
    CCSprite *spr = CCSprite::create(filename);
    CCSize sprSize = spr->getContentSize();

    spr->setAnchorPoint(ccp(0.5f,0.5f));
    spr->setPosition(ccp(sprSize.width/2.f, sprSize.height/2.f));

    setContentSize(sprSize);
    
    addChild(spr);
}

CCRect MapElement::boundingBox()
{
    if (m_mainSpr)
    {
        CCRect rect = m_mainSpr->getTextureRect();
        rect.origin.x = 0;
        rect.origin.y = 0;

        CCAffineTransform transform = m_mainSpr->nodeToParentTransform();
        transform = CCAffineTransformConcat(transform, nodeToParentTransform());

        return CCRectApplyAffineTransform(rect, transform);
    }
    
    return CCRectApplyAffineTransform(CCRect(0, 0, 30, 30), nodeToParentTransform());

    CCRect aabb = CCNode::boundingBox();

    //aabb.origin.x -= aabb.size.width * getAnchorPoint().x;
    //aabb.origin.y -= aabb.size.height * getAnchorPoint().y;

    return aabb;
}

bool MapElement::isBlock( const MapElemVec &elems )
{
    return false;
}

void MapElement::collide( const MapElemVec &elems )
{

}

void MapElement::playAnimation( const std::string &name, const std::string &animSubName )
{
    if (CCAnimation *animInfo = MapAnimation::sharedMapAnimation()->createAnimation(name, animSubName))
    {
        if (!m_mainSpr)
        {
            m_mainSpr = CCSprite::create();
            m_mainSpr->setAnchorPoint(ccp(0.5, 0.5));
            addChild(m_mainSpr);
        }
        
        CCAction * action = CCRepeatForever::create(CCAnimate::create(animInfo));
        action->setTag(MAP_ELEM_ANIM_TAG);

        m_mainSpr->stopActionByTag(MAP_ELEM_ANIM_TAG);
        m_mainSpr->runAction(action);
    }
}

void MapElement::playAnimation( const std::string &subName )
{
    playAnimation(m_animName, subName);
}
