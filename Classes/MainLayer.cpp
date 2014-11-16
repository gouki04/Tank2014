#include "MainLayer.h"
#include "Map.h"
#include "MapCollideMgr.h"
#include "support\CCPointExtension.h"
#include "MapAnimation.h"

USING_NS_CC;

MainLayer::MainLayer()
{

}

MainLayer::~MainLayer()
{

}

MainLayer * MainLayer::create()
{
    MainLayer *layer = new MainLayer;
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    
    CC_SAFE_DELETE(layer);
    return 0;
}

bool MainLayer::init()
{
    m_map = Map::createWithSize(10, 10);
    m_map->setAnchorPoint(ccp(0, 0));
    //m_map->setPosition(ccp(20, 20));

    addChild(m_map, 1);

    MapAnimation::sharedMapAnimation()->init();

    MapCollideMgr *collideMgr = MapCollideMgr::sharedMapCollideMgr();
    collideMgr->setMap(m_map);

    return true;
}
