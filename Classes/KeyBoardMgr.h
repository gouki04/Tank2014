#ifndef KeyBoardMgr_h__
#define KeyBoardMgr_h__

#include "base\CCRef.h"

namespace gouki {
    class KeyBoardMgr : public cocos2d::Ref
    {
    public:
        KeyBoardMgr();
        virtual ~KeyBoardMgr();

        bool isKeyDown(int virKey);
        bool isKeyUp(int virKey);

    public:
        static KeyBoardMgr *sharedKeyBoardMgr();
        static void purgeSharedKeyBoardMgr();
    };
}

#endif // KeyBoardMgr_h__
