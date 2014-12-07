#ifndef MapUserTank_h__
#define MapUserTank_h__

#include "MapTank.h"

namespace gouki {
    class MapUserTank : public MapTank
    {
    public:
        MapUserTank();
        virtual ~MapUserTank();

        virtual bool init() override;

        static MapUserTank *create();

        virtual eMapElement getElemType() override { return eMapElement::UserTank; }
        virtual std::string getElemTypeStr() override { return "UserTank"; }

    protected:
        int m_level;
    };
}

#endif // MapUserTank_h__
