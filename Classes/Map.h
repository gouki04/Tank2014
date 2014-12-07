#ifndef Map_h__
#define Map_h__

#include "cocos\2d\CCNode.h"
#include <vector>

namespace Json {
    class Value;
}

namespace gouki {
    class MapElement;
    class MapTank;
    class MapBullet;

    typedef std::vector<MapTank*> MapTankVec;
    typedef std::vector<MapBullet*> MapBulletVec;
    typedef std::vector<cocos2d::Vec2> PointVec;

    class Map : public cocos2d::Node
    {
    public:
        Map();
        virtual ~Map();

        virtual bool initWithSize(int row, int col);

        cocos2d::Size getSize() const;

        int getRow() { return m_row; }
        int getCol() { return m_col; }

        MapElement *getElementAt(int r, int c);

        cocos2d::Vec2 convert2PixelPos(int r, int c);

        cocos2d::Vec2 convert2IndexPos(const cocos2d::Vec2 &pos);
        void convert2IndexPos(const cocos2d::Vec2 &pos, int &r, int &c);

        virtual void addTank(const cocos2d::Vec2 &pos);

        virtual void addEnemyTank(const cocos2d::Vec2 &pos, int level);

        virtual void addBase(const cocos2d::Vec2 &pos);

        virtual void addBullet(MapBullet *bullet);

        virtual void addBomb(const cocos2d::Vec2 &pos);
        virtual void addSmallBomb(const cocos2d::Vec2 &pos);

        MapTankVec &getUserTanks() { return m_userTanks; }

        MapTankVec &getEnemyTanks() { return m_enemyTanks; }

        MapBulletVec &getBullets() { return m_bullets; }

        MapElement *getBase() { return m_base; }

        virtual void removeBullet(MapBullet *bullet);

        virtual void removeUserTank(MapTank *tank);

        virtual void removeEnemyTank(MapTank *tank);

        virtual void removeTank(MapTank *tank);

        virtual void removeBase();

        virtual void removeElement(MapElement *elem);

        virtual void playAnimationAt(const cocos2d::Vec2 &pos, const std::string &animName, const std::string &animSubName);

        static Map *createWithSize(int row, int col);

    protected:
        void animCallback(cocos2d::Node *spr);

        Json::Value *parseJsonFile(const std::string &filename);

        void updateAddEnemy(float dt);

    protected:
        int m_row, m_col;
        MapElement ***m_data;

        MapTankVec m_userTanks;
        MapTankVec m_enemyTanks;

        MapBulletVec m_bullets;
        MapElement *m_base;

        PointVec m_userStarts;
        PointVec m_enemyStarts;

        int m_enemyCount;
    };
}

#endif // Map_h__
