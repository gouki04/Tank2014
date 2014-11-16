//#include "MapRender.h"
//#include "Map.h"
//#include "sprite_nodes\CCSprite.h"
//#include "support\CCPointExtension.h"
//
//USING_NS_CC;
//
//void MapRender::draw( Map *m )
//{
//    //CCPoint basePos = m->getPosition();
//
//    //for (int r = 0; r < m->getRow(); ++r)
//    //{
//    //    for (int c = 0; c < m->getCol(); ++c)
//    //    {
//    //        const eMapElement &elem = m->getElementAt(r, c);
//    //        if (CCSprite *renderElem = getRenderElemBy(elem))
//    //        {
//    //            renderElem->setPosition(ccp(basePos.x + c * MAP_ELEM_WIDTH, basePos.y + r * MAP_ELEM_HEIGHT));
//    //            renderElem->draw();
//    //        }
//    //    }
//    //}
//}
//
//bool MapRender::init()
//{
//    m_renderElems[eMapElement::Null] = 0;
//    m_renderElems[eMapElement::Brick] = CCSprite::create("brick.png");
//    m_renderElems[eMapElement::Steel] = CCSprite::create("steel.png");
//
//    RenderElementMap::iterator iter = m_renderElems.begin();
//    for (; iter != m_renderElems.end(); ++iter)
//    {
//        if (CCSprite *spr = iter->second)
//        {
//            spr->retain();
//        }
//    }
//
//    return true;
//}
//
//cocos2d::CCSprite * MapRender::getRenderElemBy( const eMapElement &elem )
//{
//    RenderElementMap::iterator iter = m_renderElems.find(elem);
//    if (iter != m_renderElems.end())
//    {
//        return iter->second;
//    }
//    
//    return 0;
//}
//
//MapRender * MapRender::create()
//{
//    MapRender *render = new MapRender;
//    if (render && render->init())
//    {
//        render->autorelease();
//        return render;
//    }
//
//    CC_SAFE_DELETE(render);
//    return 0;
//}
