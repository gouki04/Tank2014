#ifndef MapCommon_h__
#define MapCommon_h__

#include <stdlib.h>
#include <vector>

namespace gouki {

#define ENUM_CLASS_DECLARE(cls_type) \
    public: ENUM  m_val;  \
    public: \
    cls_type ( const ENUM& s): m_val(s) {} ;  \
    cls_type ( const cls_type& s): m_val(s.m_val) {}; \
    bool operator == ( const ENUM& cs ) const {   \
    if ( m_val == cs ) return true; \
            else return false; }    \
            bool operator == (const cls_type& cs) const { \
            if (m_val == cs.m_val) return true; \
            else return false; } \
            operator ENUM() const { return m_val; };

    class eMapElement
    {
    public:
        enum ENUM {
            Invalid = '?',
            Null = '0',
            Wall = '#',
            Brick = '1',
            Steel = '2',
            Grass = '3',
            UserTank = 'U',
            EnemyTank = 'E',
            Bullet = 'B',
            Base = 'M',
            Item = 'I',
        };

        ENUM_CLASS_DECLARE(eMapElement)
    };

    class eMapLayerOrder
    {
    public:
        enum ENUM {
            Invalid = 0,
            Background,
            Object,
            Foreground
        };

        ENUM_CLASS_DECLARE(eMapLayerOrder)
    };

    class eDirection
    {
    public:
        enum ENUM {
            Invalid = -1,
            Up,
            Down,
            Left,
            Right
        };

        ENUM_CLASS_DECLARE(eDirection)

        static ENUM random() {
            int n = rand() % 4;

            if (n == 0) {
                return Left;
            } else if (n == 1) {
                return Right;
            } else if (n == 2) {
                return Up;
            } else {
                return Down;
            }
        }
    };

#define MAP_ELEM_WIDTH  32.f
#define MAP_ELEM_HEIGHT 32.f

    class MapElement;
    typedef std::vector<MapElement*> MapElemVec;
}

#endif // MapCommon_h__
