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

/* ��ͼ
 **/
class Map : public cocos2d::CCNode
{
public:
    Map();
    virtual ~Map();

    /* @brief ������������ʼ����ͼ
     * @param row col ��ͼ��������
     * @return �Ƿ�ɹ���ʼ��
     * 
     * @TODO ���ڻ�����ص�ͼ�����س����ĵ�λ����Щ�Ժ�Ҫ����һ���ӿ�ר�ų�ʼ����һ��
     **/
    virtual bool initWithSize(int row, int col);

    /* @brief ��ȡ��ͼ�Ĵ�С�����ش�С��
     * @return ��ͼ�����ش�С
     **/
    cocos2d::CCSize getSize() const;

    /* @brief ��ȡ��ͼ����/��
     **/
    int getRow() { return m_row; }
    int getCol() { return m_col; }

    /* @brief ��ȡ��ͼָ��λ�õĵر�Ԫ��
     * @param r c ����
     * @return �ر�Ԫ�أ����᷵���������͵�Ԫ�أ�
     **/
    MapElement *getElementAt(int r, int c);

    /* @brief ����������תΪ��������
     * @param r c ����
     * @return ���ж�Ӧ���������꣨�ø��ӵ����½����꣩
     **/
    cocos2d::CCPoint convert2PixelPos(int r, int c);

    /* @brief ����������תΪ��������
     * @param pos ��������
     * @return ��Ӧ�ĸ������꣨������������Ǹ���ģ�����ȡ����
     **/
    cocos2d::CCPoint convert2IndexPos(const cocos2d::CCPoint &pos);

    /* @brief ����������תΪ��������
     * @param pos ��������
     * @param[out] r c ��Ӧ�ĸ�����������У��������������ȡ�����ģ�
     **/
    void convert2IndexPos(const cocos2d::CCPoint &pos, int &r, int &c);

    /* @brief ��ָ��λ�����һ���û�̹��
     * @param pos ̹�˵ĳ�ʼλ��
     **/
    virtual void addTank(const cocos2d::CCPoint &pos);

    /* @brief ��ָ��λ�����һ���з�̹��
     * @param pos ̹�˵ĳ�ʼλ��
     * @param level ̹�˵ĵȼ�
     **/
    virtual void addEnemyTank(const cocos2d::CCPoint &pos, int level);

    virtual void addBase(const cocos2d::CCPoint &pos);

    /* @brief ���һ���ӵ�
     * @param bullet Ҫ��ӵ��ӵ�
     * @detail ע��������ֱ�ӰѴ����õ��ӵ��������ˣ���Ϊ�ӵ��Ǹ���̹���Լ������ģ�����map�����𴴽��ӵ���һ��
     **/
    virtual void addBullet(MapBullet *bullet);

    virtual void addBomb(const cocos2d::CCPoint &pos);
    virtual void addSmallBomb(const cocos2d::CCPoint &pos);

    /* @brief ��ȡ�����û�̹��
     * @return �����û�̹�˵��б�
     **/
    MapTankVec &getUserTanks() { return m_userTanks; }

    /* @brief ��ȡ���ез�̹��
     * @return ���ез�̹�˵��б�
     **/
    MapTankVec &getEnemyTanks() { return m_enemyTanks; }

    /* @brief ��ȡ�����ӵ�
     * @return �����ӵ����б����ֵ��ң�
     **/
    MapBulletVec &getBullets() { return m_bullets; }

    MapElement *getBase() { return m_base; }

    /* @brief �ӵ�ͼ��ɾ��һ���ӵ�
     * @param bullet Ҫɾ�����ӵ�
     **/
    virtual void removeBullet(MapBullet *bullet);

    /* @brief �ӵ�ͼ��ɾ��һ���û�̹��
     * @param tank Ҫɾ�����û�̹��
     **/
    virtual void removeUserTank(MapTank *tank);

    /* @brief �ӵ�ͼ��ɾ��һ���з�̹��
     * @param tank Ҫɾ���ĵз�̹��
     **/
    virtual void removeEnemyTank(MapTank *tank);

    /* @brief �ӵ�ͼ��ɾ��һ��̹�ˣ����ֵ��ң�
     * @param tank Ҫɾ����̹��
     **/
    virtual void removeTank(MapTank *tank);

    virtual void removeBase();

    /* @brief �ӵ�ͼ��ɾ��һ��Ԫ��
     * @param elem Ҫɾ����Ԫ��
     * 
     * @detail ͨ�÷���������ɾ������ĵ�ͼԪ�أ������ر�Ԫ�أ�
     **/
    virtual void removeElement(MapElement *elem);

    virtual void playAnimationAt(const cocos2d::CCPoint &pos, const std::string &animnName, const std::string &animSubName);

    /* @brief ��������
     * @param row col ��ͼ������
     * @return �����õ�Map��ʧ�ܷ���NULL
     **/
    static Map *createWithSize(int row, int col);

protected:
    void animCallback(CCNode *spr);

    Json::Value *parseJsonFile(const std::string &filename);

    void updateAddEnemy(float dt);

protected:
    int m_row, m_col;        ///< ��ͼ������
    MapElement ***m_data;    ///< �ر�Ԫ�أ�2ά��

    MapTankVec m_userTanks;  ///< �û�̹���б�
    MapTankVec m_enemyTanks; ///< �з�̹���б�

    MapBulletVec m_bullets;  ///< �ӵ��б�
    MapElement *m_base;

    PointVec m_userStarts;
    PointVec m_enemyStarts;

    int m_enemyCount;
};

#endif // Map_h__
