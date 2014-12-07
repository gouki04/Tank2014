#ifndef MapEnemyTank_h__
#define MapEnemyTank_h__

#include "MapTank.h"

namespace gouki {

    class MapEnemyTank : public MapTank
    {
    public:
        MapEnemyTank();
        virtual ~MapEnemyTank();

        virtual bool initWithLevel(int level);

        static MapEnemyTank *createWithLevel(int level);

        virtual eMapElement getElemType() override { return eMapElement::EnemyTank; }
        virtual std::string getElemTypeStr() override { return "EnemyTank"; }

    protected:
        int m_level;
    };
}

#endif // MapEnemyTank_h__
