#include "MainScene.h"
#include "MainLayer.h"
#include "CCDirector.h"
#include "support\CCPointExtension.h"

USING_NS_CC;

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

MainScene * MainScene::create()
{
    MainScene *scene = new MainScene;
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    
    CC_SAFE_DELETE(scene);
    return 0;
}

void MainScene::onEnter()
{
    CCScene::onEnter();

    MainLayer *layer = MainLayer::create();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scale = winSize.height / (28 * 30);

    layer->setAnchorPoint(ccp(0.f, 0.f));
    layer->setScale(scale);

    addChild(layer);
}
