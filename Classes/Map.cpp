#include "Map.h"
#include "json/json.h"
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "2d/CCSprite.h"
#include "2d/CCActionInterval.h"
#include "2d/CCActionInstant.h"
#include "CCFileUtils.h"
#include "CCCommon.h"
#include "MapCommon.h"
#include "MapElementFactory.h"
#include "MapElement.h"
#include "MapUserTank.h"
#include "MapEnemyTank.h"
#include "MapBullet.h"
#include "MapBase.h"
#include "MapAnimation.h"

namespace gouki {
    Map::Map()
        : m_row(0)
        , m_col(0)
        , m_base(nullptr) {

    }

    Map::~Map() {

    }

    Map *Map::createWithSize(int row, int col) {
        Map *map = new Map;
        if (map && map->initWithSize(row, col))
        {
            map->autorelease();
            return map;
        }
    
        CC_SAFE_DELETE(map);
        return nullptr;
    }

    bool Map::initWithSize(int row, int col) {
        Json::Value *root = parseJsonFile("map.json");
        if (!root) {
            return false;
        }

        Json::Value &lvRoot = (*root)["Level_1"];

        m_row = lvRoot["Row"].asInt();
        m_col = lvRoot["Col"].asInt();

        Json::Value mapdata = lvRoot["Data"];

        m_data = new MapElement **[m_row];
        for (int r = 0; r < m_row; ++r) {
            m_data[r] = new MapElement *[m_col];
            for (int c = 0; c < m_col; ++c) {
                eMapElement elemtype = static_cast<eMapElement::ENUM>(mapdata[m_row-1-r].asString()[c]);

                if (MapElement *elem = MapElementFactory::createElem(elemtype)) {
                    elem->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
                    elem->setMap(this);
                    elem->setPosition(convert2PixelPos(r, c));

                    addChild(elem);

                    m_data[r][c] = elem;
                } else {
                    m_data[r][c] = 0;
                }
            }
        }

        m_enemyCount = lvRoot["EnemyCount"].asInt();

        // add user tank
        Json::Value &jUserStarts = lvRoot["UserStart"];
        for (Json::Value::ArrayIndex i = 0; i < jUserStarts.size(); ++i) {
            auto p = cocos2d::Vec2(jUserStarts[i]["X"].asInt() * MAP_ELEM_WIDTH, jUserStarts[i]["Y"].asInt() * MAP_ELEM_HEIGHT);
            m_userStarts.push_back(p);
        }

        addTank(m_userStarts[0]);

        // add enemy
        Json::Value &jEnemyStarts = lvRoot["EnemyStart"];
        for (Json::Value::ArrayIndex i = 0; i < jEnemyStarts.size(); ++i) {
            auto p = cocos2d::Vec2(jEnemyStarts[i]["X"].asInt() * MAP_ELEM_WIDTH, jEnemyStarts[i]["Y"].asInt() * MAP_ELEM_HEIGHT);
            m_enemyStarts.push_back(p);
        }

        for (PointVec::size_type i = 0; i < m_enemyStarts.size(); ++i) {
            addEnemyTank(m_enemyStarts[i], 1);
        }

        // add base
        Json::Value &jBase = lvRoot["Base"];
        auto basePos = cocos2d::Vec2(jBase["X"].asInt() * MAP_ELEM_WIDTH, jBase["Y"].asInt() * MAP_ELEM_HEIGHT);
        addBase(basePos);

        cocos2d::Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(Map::updateAddEnemy), this, 5, false);

        return true;
    }

    cocos2d::Size Map::getSize() const {
        return cocos2d::Size(m_col * MAP_ELEM_WIDTH, m_row * MAP_ELEM_HEIGHT);
    }

    cocos2d::Vec2 Map::convert2PixelPos( int r, int c ) {
        return cocos2d::Vec2(c * MAP_ELEM_WIDTH + MAP_ELEM_WIDTH / 2.f, 
            r * MAP_ELEM_HEIGHT + MAP_ELEM_HEIGHT / 2.f);
    }

    cocos2d::Vec2 Map::convert2IndexPos( const cocos2d::Vec2 &pos ) {
        int r = (pos.y - MAP_ELEM_HEIGHT / 2.f) / MAP_ELEM_HEIGHT;
        int c = (pos.x - MAP_ELEM_WIDTH / 2.f) / MAP_ELEM_WIDTH;

        return cocos2d::Vec2(c, r);
    }

    void Map::convert2IndexPos( const cocos2d::Vec2 &pos, int &r, int &c ) {
        r = (pos.y - MAP_ELEM_HEIGHT / 2.f) / MAP_ELEM_HEIGHT;
        c = (pos.x - MAP_ELEM_WIDTH / 2.f) / MAP_ELEM_WIDTH;
    }

    void Map::addTank( const cocos2d::Vec2 &pos ) {
        auto tank = MapUserTank::create();
        tank->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        tank->setSpeed(100);
        tank->setDirection(eDirection::Up);
        tank->setPosition(pos);
        tank->setMap(this);

        addChild(tank);

        m_userTanks.push_back(tank);
    }

    void Map::addEnemyTank( const cocos2d::Vec2 &pos, int level ) {
        auto tank = MapEnemyTank::createWithLevel(level);
        tank->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
        tank->setSpeed(80);
        tank->setDirection(eDirection::Down);
        tank->setPosition(pos);
        tank->setMap(this);

        addChild(tank);

        m_enemyTanks.push_back(tank);

        m_enemyCount--;
    }

    void Map::addBullet( MapBullet *bullet ) {
        auto iter = std::find(m_bullets.begin(), m_bullets.end(), bullet);
        if (iter == m_bullets.end()) {
            m_bullets.push_back(bullet);
        }

        bullet->setMap(this);
        addChild(bullet);
    }

    void Map::addBase( const cocos2d::Vec2 &pos ) {
        auto base = MapBase::create();
        base->setPosition(pos);
        base->setMap(this);

        m_base = base;

        addChild(base);
    }

    void Map::addBomb( const cocos2d::Vec2 &pos ) {
        playAnimationAt(pos, "Bomb", "idle");
    }

    void Map::addSmallBomb( const cocos2d::Vec2 &pos ) {
        playAnimationAt(pos, "SmallBomb", "idle");
    }

    void Map::removeBullet( MapBullet *bullet ) {
        auto iter = std::find(m_bullets.begin(), m_bullets.end(), bullet);
        if (iter != m_bullets.end())
        {
            m_bullets.erase(iter);
        }

        removeChild(bullet, true);
    }

    void Map::removeUserTank( MapTank *tank ) {
        auto iter = std::find(m_userTanks.begin(), m_userTanks.end(), tank);
        if (iter != m_userTanks.end())
        {
            m_userTanks.erase(iter);
        }

        removeChild(tank, true);
    }

    void Map::removeEnemyTank( MapTank *tank ) {
        auto iter = std::find(m_enemyTanks.begin(), m_enemyTanks.end(), tank);
        if (iter != m_enemyTanks.end()) {
            m_enemyTanks.erase(iter);
        }

        removeChild(tank, true);
    }

    void Map::removeTank( MapTank *tank ) {
        if (tank->getElemType() == eMapElement::UserTank) {
            removeUserTank(tank);
        } else {
            removeEnemyTank(tank);
        }
    }

    void Map::removeBase() {
        if (m_base) {
            removeChild(m_base, true);
            m_base = 0;
        }
    }

    void Map::removeElement( MapElement *elem ) {
        eMapElement elemType = elem->getElemType();
        if (elemType == eMapElement::UserTank) {
            removeUserTank((MapUserTank*)elem);
        } else if (elemType == eMapElement::EnemyTank) {
            removeEnemyTank((MapEnemyTank*)elem);
        } else if (elemType == eMapElement::Bullet) {
            removeBullet((MapBullet*)elem);
        } else if (elemType == eMapElement::Base) {
            removeBase();
        } else {
            const cocos2d::Vec2 &pos = elem->getPosition();

            int r, c;
            convert2IndexPos(pos, r, c);

            if (m_data[r][c] == elem) {
                m_data[r][c] = 0;
            } else {
                CCLOG("remove elem error!!");
            }

            removeChild(elem, true);
        }
    }

    MapElement * Map::getElementAt( int r, int c ) {
        if (r >= 0 && r < m_row && c >= 0 && c < m_col) {
            return m_data[r][c];
        } else {
            return 0;
        }
    }

    void Map::playAnimationAt( const cocos2d::Vec2 &pos, const std::string &animnName, const std::string &animSubName ) {
        if (auto animInfo = MapAnimation::sharedMapAnimation()->createAnimation(animnName, animSubName)) {
            auto spr = cocos2d::Sprite::create();
            spr->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
            spr->setPosition(pos);
            addChild(spr);

            auto action = cocos2d::Sequence::createWithTwoActions(
                cocos2d::Animate::create(animInfo), 
                cocos2d::CallFuncN::create(CC_CALLBACK_1(Map::animCallback, this)));

            spr->runAction(action);
        }
    }

    void Map::animCallback( cocos2d::Node *spr ) {
        spr->removeFromParentAndCleanup(true);
    }

    Json::Value * Map::parseJsonFile( const std::string &filename ) {
        auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile("map.json");

        Json::Reader reader;
        Json::Value *root = new Json::Value;
        const char *beginDoc = (const char*)(fileData.getBytes());
        const char *endDoc = (const char*)(fileData.getBytes() + fileData.getSize());

        if (!reader.parse(beginDoc, endDoc, *root)) {
            cocos2d::MessageBox(reader.getFormatedErrorMessages().c_str(), "Json Parse Error!");
            return nullptr;
        }

        fileData.clear();

        return root;
    }

    void Map::updateAddEnemy( float dt ) {
        if (m_enemyCount > 0) {
            int idx = rand() % (m_enemyStarts.size());
            addEnemyTank(m_enemyStarts[idx], 1);
        } else {
            cocos2d::Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(Map::updateAddEnemy), this);
        }
    }
}