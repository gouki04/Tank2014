#include "MapElement.h"
#include "MapAnimation.h"
#include "2d/CCSprite.h"
#include "2d/CCActionInterval.h"

#define MAP_ELEM_ANIM_TAG 99

namespace gouki {
    MapElement::MapElement()
        : m_mainSpr(0) {

    }

    MapElement::~MapElement() {

    }

    cocos2d::Rect MapElement::getBoundingBox() const {
        if (m_mainSpr) {
            cocos2d::Rect rect = m_mainSpr->getTextureRect();
            rect.origin.x = 0;
            rect.origin.y = 0;

            auto transform = m_mainSpr->getNodeToParentAffineTransform();
            transform = AffineTransformConcat(transform, getNodeToParentAffineTransform());

            return RectApplyAffineTransform(rect, transform);
        }

        return RectApplyAffineTransform(cocos2d::Rect(0, 0, 30, 30), getNodeToParentAffineTransform());

        cocos2d::Rect aabb = Node::getBoundingBox();

        //aabb.origin.x -= aabb.size.width * getAnchorPoint().x;
        //aabb.origin.y -= aabb.size.height * getAnchorPoint().y;

        return aabb;
    }

    bool MapElement::isBlock( const MapElemVec &elems ) {
        return false;
    }

    void MapElement::collide( const MapElemVec &elems ) {

    }

    void MapElement::playAnimation( const std::string &name, const std::string &animSubName ) {
        if (auto animInfo = MapAnimation::sharedMapAnimation()->createAnimation(name, animSubName)) {
            if (!m_mainSpr) {
                m_mainSpr = cocos2d::Sprite::create();
                m_mainSpr->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
                addChild(m_mainSpr);
            }

            auto action = cocos2d::RepeatForever::create(cocos2d::Animate::create(animInfo));
            action->setTag(MAP_ELEM_ANIM_TAG);

            m_mainSpr->stopActionByTag(MAP_ELEM_ANIM_TAG);
            m_mainSpr->runAction(action);
        }
    }

    void MapElement::playAnimation( const std::string &subName ) {
        playAnimation(m_animName, subName);
    }

    void MapElement::setMainAnimName( const std::string &animName ) {
        m_animName = animName;
    }
}
