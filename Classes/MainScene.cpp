#include "MainScene.h"
#include "MainLayer.h"
#include "cocos/base/CCDirector.h"

namespace gouki {
    MainScene::MainScene() {

    }

    MainScene::~MainScene() {

    }

    MainScene *MainScene::create() {
        MainScene *scene = new MainScene;
        if (scene && scene->init()) {
            scene->autorelease();
            return scene;
        }

        CC_SAFE_DELETE(scene);
        return nullptr;
    }

    void MainScene::onEnter() {
        cocos2d::Scene::onEnter();

        MainLayer *layer = MainLayer::create();

        cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
        float scale = winSize.height / (28.0 * 32.0);

        layer->setAnchorPoint(cocos2d::Vec2(0.f, 0.f));
        layer->setScale(scale);

        addChild(layer);
    }
}