#include "MainLayer.h"
#include "Map.h"
#include "MapAnimation.h"
#include "MapCollideMgr.h"

namespace gouki {
	MainLayer::MainLayer() {
	
	}
	
	MainLayer::~MainLayer() {
	
	}
	
	MainLayer *MainLayer::create() {
	    MainLayer *layer = new MainLayer;
	    if (layer && layer->init()) {
	        layer->autorelease();
	        return layer;
	    }
	
	    CC_SAFE_DELETE(layer);
	    return nullptr;
	}
	
	bool MainLayer::init() {
        m_map = Map::createWithSize(10, 10);
        m_map->setAnchorPoint(cocos2d::Vec2(0, 0));
        //m_map->setPosition(ccp(20, 20));

        addChild(m_map, 1);

        MapAnimation::sharedMapAnimation()->init();

        MapCollideMgr *collideMgr = MapCollideMgr::sharedMapCollideMgr();
        collideMgr->setMap(m_map);

	    return true;
	}
}