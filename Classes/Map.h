#ifndef Map_h__
#define Map_h__

#include "base_nodes\CCNode.h"
#include "MapCommon.h"
#include "cocoa\CCGeometry.h"
#include <vector>

class MapElement;
class MapTank;
class MapBullet;

namespace Json {
    class Value;
}

typedef std::vector<MapTank*> MapTankVec;
typedef std::vector<MapBullet*> MapBulletVec;
typedef std::vector<cocos2d::CCPoint> PointVec;

/* 地图
 **/
class Map : public cocos2d::CCNode
{
public:
    Map();
    virtual ~Map();

    /* @brief 根据行列数初始化地图
     * @param row col 地图的行列数
     * @return 是否成功初始化
     * 
     * @TODO 现在还会加载地图，加载场景的单位，这些以后要开另一个接口专门初始化这一块
     **/
    virtual bool initWithSize(int row, int col);

    /* @brief 获取地图的大小（像素大小）
     * @return 地图的像素大小
     **/
    cocos2d::CCSize getSize() const;

    /* @brief 获取地图的行/列
     **/
    int getRow() { return m_row; }
    int getCol() { return m_col; }

    /* @brief 获取地图指定位置的地表元素
     * @param r c 行列
     * @return 地表元素（不会返回其他类型的元素）
     **/
    MapElement *getElementAt(int r, int c);

    /* @brief 将格子坐标转为像素坐标
     * @param r c 行列
     * @return 行列对应的像素坐标（该格子的左下角坐标）
     **/
    cocos2d::CCPoint convert2PixelPos(int r, int c);

    /* @brief 将像素坐标转为格子坐标
     * @param pos 像素坐标
     * @return 对应的格子坐标（这个格子坐标是浮点的，不会取整）
     **/
    cocos2d::CCPoint convert2IndexPos(const cocos2d::CCPoint &pos);

    /* @brief 将像素坐标转为格子坐标
     * @param pos 像素坐标
     * @param[out] r c 对应的格子坐标的行列（这个格子坐标是取整过的）
     **/
    void convert2IndexPos(const cocos2d::CCPoint &pos, int &r, int &c);

    /* @brief 在指定位置添加一辆用户坦克
     * @param pos 坦克的初始位置
     **/
    virtual void addTank(const cocos2d::CCPoint &pos);

    /* @brief 在指定位置添加一辆敌方坦克
     * @param pos 坦克的初始位置
     * @param level 坦克的等级
     **/
    virtual void addEnemyTank(const cocos2d::CCPoint &pos, int level);

    virtual void addBase(const cocos2d::CCPoint &pos);

    /* @brief 添加一颗子弹
     * @param bullet 要添加的子弹
     * @detail 注意这里是直接把创建好的子弹传进来了，因为子弹是根据坦克自己创建的，所以map不负责创建子弹这一步
     **/
    virtual void addBullet(MapBullet *bullet);

    virtual void addBomb(const cocos2d::CCPoint &pos);
    virtual void addSmallBomb(const cocos2d::CCPoint &pos);

    /* @brief 获取所有用户坦克
     * @return 所有用户坦克的列表
     **/
    MapTankVec &getUserTanks() { return m_userTanks; }

    /* @brief 获取所有敌方坦克
     * @return 所有敌方坦克的列表
     **/
    MapTankVec &getEnemyTanks() { return m_enemyTanks; }

    /* @brief 获取所有子弹
     * @return 所有子弹的列表（不分敌我）
     **/
    MapBulletVec &getBullets() { return m_bullets; }

    MapElement *getBase() { return m_base; }

    /* @brief 从地图中删除一颗子弹
     * @param bullet 要删除的子弹
     **/
    virtual void removeBullet(MapBullet *bullet);

    /* @brief 从地图中删除一辆用户坦克
     * @param tank 要删除的用户坦克
     **/
    virtual void removeUserTank(MapTank *tank);

    /* @brief 从地图中删除一辆敌方坦克
     * @param tank 要删除的敌方坦克
     **/
    virtual void removeEnemyTank(MapTank *tank);

    /* @brief 从地图中删除一辆坦克（不分敌我）
     * @param tank 要删除的坦克
     **/
    virtual void removeTank(MapTank *tank);

    virtual void removeBase();

    /* @brief 从地图中删除一个元素
     * @param elem 要删除的元素
     * 
     * @detail 通用方法，可以删除任意的地图元素（包括地表元素）
     **/
    virtual void removeElement(MapElement *elem);

    virtual void playAnimationAt(const cocos2d::CCPoint &pos, const std::string &animnName, const std::string &animSubName);

    /* @brief 构建函数
     * @param row col 地图的行列
     * @return 构建好的Map，失败返回NULL
     **/
    static Map *createWithSize(int row, int col);

protected:
    void animCallback(CCNode *spr);

    Json::Value *parseJsonFile(const std::string &filename);

    void updateAddEnemy(float dt);

protected:
    int m_row, m_col;        ///< 地图的行列
    MapElement ***m_data;    ///< 地表元素（2维表）

    MapTankVec m_userTanks;  ///< 用户坦克列表
    MapTankVec m_enemyTanks; ///< 敌方坦克列表

    MapBulletVec m_bullets;  ///< 子弹列表
    MapElement *m_base;

    PointVec m_userStarts;
    PointVec m_enemyStarts;

    int m_enemyCount;
};

#endif // Map_h__
