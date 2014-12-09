#include "MapElement.h"
#include "MapAnimation.h"
#include "2d/CCSprite.h"
#include "2d/CCActionInterval.h"

#define MAP_ELEM_ANIM_TAG 99

namespace gouki {
    MapElement::MapElement()
        : m_mainSpr(0)
        , m_debugDrawNode(nullptr) {
        m_debugDrawNode = cocos2d::DrawNode::create();
        addChild(m_debugDrawNode);
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

    void MapElement::draw( cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags ) {
        cocos2d::Node::draw(renderer, transform, flags);

        if (m_debugDrawNode) {
            m_debugDrawNode->clear();

            cocos2d::Rect aabb = getBoundingBox();

            cocos2d::Vec2 verties[4] = {
                cocos2d::Vec2(0.f, 0.f),
                cocos2d::Vec2(aabb.size.width, 0.f),
                cocos2d::Vec2(aabb.size.width, aabb.size.height),
                cocos2d::Vec2(0.f, aabb.size.height)
            };

            m_debugDrawNode->drawPoly(verties, 4, true, cocos2d::Color4F(1.f, 0.f, 0.f, 1.f));
        }
    }
}
