#ifndef MapUserTank_h__
#define MapUserTank_h__

#include "MapTank.h"

class MapUserTank : public MapTank
{
public:
    MapUserTank();
    ~MapUserTank();

    virtual bool init();

    virtual void draw();

    static MapUserTank *create();

    virtual eMapElement getElemType() { return eMapElement::UserTank; }
    virtual std::string getElemTypeStr() { return "UserTank"; }
};

#endif // MapUserTank_h__
