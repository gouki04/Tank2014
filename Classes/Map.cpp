#include "Map.h"
#include "MapElement.h"
#include "MapElementFactory.h"
#include "support\CCPointExtension.h"
#include "platform\CCFileUtils.h"
#include "json\json.h"
#include "MapUserTank.h"
#include "MapEnemyTank.h"
#include "MapBullet.h"
#include "MapBase.h"
#include <algorithm>
#include "MapAnimation.h"
#include "sprite_nodes\CCAnimation.h"
#include "sprite_nodes\CCSprite.h"
#include "actions\CCActionInterval.h"
#include "actions\CCActionInstant.h"
#include "CCDirector.h"
#include "CCScheduler.h"

USING_NS_CC;

Map::Map()
: m_row(0)
, m_col(0)
, m_base(0)
{

}

Map::~Map()
{
}

Map * Map::createWithSize(int row, int col)
{
    Map *map = new Map;
    if (map && map->initWithSize(row, col))
    {
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return 0;
}

bool Map::initWithSize(int row, int col)
{
    Json::Value *root = parseJsonFile("map.json");
    if (!root)
        return false;
    
    Json::Value &lvRoot = (*root)["Level_1"];

    m_row = lvRoot["Row"].asInt();
    m_col = lvRoot["Col"].asInt();

    Json::Value mapdata = lvRoot["Data"];

    m_data = new MapElement **[m_row];
    for (int r = 0; r < m_row; ++r)
    {
        m_data[r] = new MapElement *[m_col];
        for (int c = 0; c < m_col; ++c)
        {
            eMapElement elemtype = static_cast<eMapElement::ENUM>(mapdata[m_row-1-r].asString()[c]);
            
            if (MapElement *elem = MapElementFactory::create(elemtype))
            {
                elem->setAnchorPoint(ccp(0.5f, 0.5f));
                elem->setMap(this);
                elem->setPosition(convert2PixelPos(r, c));

                addChild(elem);

                m_data[r][c] = elem;
            }
            else
            {
                m_data[r][c] = 0;
            }
        }
    }

    m_enemyCount = lvRoot["EnemyCount"].asInt();

    // add user tank
    Json::Value &jUserStarts = lvRoot["UserStart"];
    for (Json::Value::ArrayIndex i = 0; i < jUserStarts.size(); ++i)
    {
        CCPoint p = ccp(jUserStarts[i]["X"].asInt() * MAP_ELEM_WIDTH, jUserStarts[i]["Y"].asInt() * MAP_ELEM_HEIGHT);
        m_userStarts.push_back(p);
    }

    addTank(m_userStarts[0]);

    // add enemy
    Json::Value &jEnemyStarts = lvRoot["EnemyStart"];
    for (Json::Value::ArrayIndex i = 0; i < jEnemyStarts.size(); ++i)
    {
        CCPoint p = ccp(jEnemyStarts[i]["X"].asInt() * MAP_ELEM_WIDTH, jEnemyStarts[i]["Y"].asInt() * MAP_ELEM_HEIGHT);
        m_enemyStarts.push_back(p);
    }

    for (PointVec::size_type i = 0; i < m_enemyStarts.size(); ++i)
    {
        addEnemyTank(m_enemyStarts[i], 1);
    }
    
    // add base
    Json::Value &jBase = lvRoot["Base"];
    CCPoint basePos = ccp(jBase["X"].asInt() * MAP_ELEM_WIDTH, jBase["Y"].asInt() * MAP_ELEM_HEIGHT);
    addBase(basePos);

    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Map::updateAddEnemy), this, 5, false);

    return true;
}

cocos2d::CCSize Map::getSize() const
{
    return CCSize(m_col * MAP_ELEM_WIDTH, m_row * MAP_ELEM_HEIGHT);
}

cocos2d::CCPoint Map::convert2PixelPos( int r, int c )
{
    return ccp(c * MAP_ELEM_WIDTH + MAP_ELEM_WIDTH / 2.f, 
        r * MAP_ELEM_HEIGHT + MAP_ELEM_HEIGHT / 2.f);
}

cocos2d::CCPoint Map::convert2IndexPos( const cocos2d::CCPoint &pos )
{
    int r = (pos.y - MAP_ELEM_HEIGHT / 2.f) / MAP_ELEM_HEIGHT;
    int c = (pos.x - MAP_ELEM_WIDTH / 2.f) / MAP_ELEM_WIDTH;

    return ccp(c, r);
}

void Map::convert2IndexPos( const cocos2d::CCPoint &pos, int &r, int &c )
{
    r = (pos.y - MAP_ELEM_HEIGHT / 2.f) / MAP_ELEM_HEIGHT;
    c = (pos.x - MAP_ELEM_WIDTH / 2.f) / MAP_ELEM_WIDTH;
}

void Map::addTank( const cocos2d::CCPoint &pos )
{
    MapUserTank *tank = MapUserTank::create();
    tank->setAnchorPoint(ccp(0.5f, 0.5f));
    tank->setSpeed(100);
    tank->setDirection(eDirection::Up);
    tank->setPosition(pos);
    tank->setMap(this);

    addChild(tank);

    m_userTanks.push_back(tank);
}

void Map::addEnemyTank( const cocos2d::CCPoint &pos, int level )
{
    MapEnemyTank *tank = MapEnemyTank::createWithLevel(level);
    tank->setAnchorPoint(ccp(0.5f, 0.5f));
    tank->setSpeed(80);
    tank->setDirection(eDirection::Down);
    tank->setPosition(pos);
    tank->setMap(this);

    addChild(tank);

    m_enemyTanks.push_back(tank);

    m_enemyCount--;
}

void Map::addBullet( MapBullet *bullet )
{
    MapBulletVec::iterator iter = std::find(m_bullets.begin(), m_bullets.end(), bullet);
    if (iter == m_bullets.end())
    {
        m_bullets.push_back(bullet);
    }

    bullet->setMap(this);
    addChild(bullet);
}

void Map::addBase( const cocos2d::CCPoint &pos )
{
    MapBase *base = MapBase::create();
    base->setPosition(pos);
    base->setMap(this);

    m_base = base;

    addChild(base);
}

void Map::addBomb( const cocos2d::CCPoint &pos )
{
    playAnimationAt(pos, "Bomb", "idle");
}

void Map::addSmallBomb( const cocos2d::CCPoint &pos )
{
    playAnimationAt(pos, "SmallBomb", "idle");
}

void Map::removeBullet( MapBullet *bullet )
{
    MapBulletVec::iterator iter = std::find(m_bullets.begin(), m_bullets.end(), bullet);
    if (iter != m_bullets.end())
    {
        m_bullets.erase(iter);
    }

    removeChild(bullet, true);
}

void Map::removeUserTank( MapTank *tank )
{
    MapTankVec::iterator iter = std::find(m_userTanks.begin(), m_userTanks.end(), tank);
    if (iter != m_userTanks.end())
    {
        m_userTanks.erase(iter);
    }

    removeChild(tank, true);
}

void Map::removeEnemyTank( MapTank *tank )
{
    MapTankVec::iterator iter = std::find(m_enemyTanks.begin(), m_enemyTanks.end(), tank);
    if (iter != m_enemyTanks.end())
    {
        m_enemyTanks.erase(iter);
    }

    removeChild(tank, true);
}

void Map::removeTank( MapTank *tank )
{
    if (tank->getElemType() == eMapElement::UserTank)
    {
        removeUserTank(tank);
    }
    else
    {
        removeEnemyTank(tank);
    }
}

void Map::removeBase()
{
    if (m_base)
    {
        removeChild(m_base, true);
        m_base = 0;
    }
}

void Map::removeElement( MapElement *elem )
{
    eMapElement elemType = elem->getElemType();
    if (elemType == eMapElement::UserTank)
    {
        removeUserTank((MapUserTank*)elem);
    }
    else if (elemType == eMapElement::EnemyTank)
    {
        removeEnemyTank((MapEnemyTank*)elem);
    }
    else if (elemType == eMapElement::Bullet)
    {
        removeBullet((MapBullet*)elem);
    }
    else if (elemType == eMapElement::Base)
    {
        removeBase();
    }
    else
    {
        const CCPoint &pos = elem->getPosition();

        int r, c;
        convert2IndexPos(pos, r, c);

        if (m_data[r][c] == elem)
        {
            m_data[r][c] = 0;
        }
        else
        {
            CCLOG("remove elem error!!");
        }
        
        removeChild(elem, true);
    }
}

MapElement * Map::getElementAt( int r, int c )
{
    if (r >= 0 && r < m_row && c >= 0 && c < m_col)
    {
        return m_data[r][c];
    }
    else
    {
        return 0;
    }
}

void Map::playAnimationAt( const cocos2d::CCPoint &pos, const std::string &animnName, const std::string &animSubName )
{
    if (CCAnimation *animInfo = MapAnimation::sharedMapAnimation()->createAnimation(animnName, animSubName))
    {
        CCSprite *spr = CCSprite::create();
        spr->setAnchorPoint(ccp(0.5, 0.5));
        spr->setPosition(pos);
        addChild(spr);

        CCAction * action = CCSequence::create(CCAnimate::create(animInfo), CCCallFuncN::create(this, callfuncN_selector(Map::animCallback)));
        spr->runAction(action);
    }
}

void Map::animCallback( CCNode *spr )
{
    spr->removeFromParentAndCleanup(true);
}

Json::Value * Map::parseJsonFile( const std::string &filename )
{
    unsigned char *file_buffer;
    unsigned long file_size;

    file_buffer = CCFileUtils::sharedFileUtils()->getFileData("map.json", "r", &file_size);

    Json::Reader reader;
    Json::Value *root = new Json::Value;
    const char *beginDoc = (const char*)(file_buffer);
    const char *endDoc = (const char*)(file_buffer+file_size);

    if (!reader.parse(beginDoc, endDoc, *root))
    {
        CCMessageBox(reader.getFormatedErrorMessages().c_str(), "Json Parse Error!");
        return 0;
    }

    return root;
}

void Map::updateAddEnemy( float dt )
{
    if (m_enemyCount > 0)
    {
        int idx = rand() % (m_enemyStarts.size());
        addEnemyTank(m_enemyStarts[idx], 1);
    }
    else
    {
        CCDirector::sharedDirector()->getScheduler()->unscheduleSelector(schedule_selector(Map::updateAddEnemy), this);
    }
}
