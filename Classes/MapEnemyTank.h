#ifndef MapEnemyTank_h__
#define MapEnemyTank_h__

#include "MapTank.h"

class MapEnemyTank : public MapTank
{
public:
    MapEnemyTank();
    ~MapEnemyTank();

    virtual bool initWithLevel(int level);

    static MapEnemyTank *createWithLevel(int level);

    virtual eMapElement getElemType() { return eMapElement::EnemyTank; }
    virtual std::string getElemTypeStr() { return "EnemyTank"; }

protected:
    int m_level;
};

#endif // MapEnemyTank_h__
