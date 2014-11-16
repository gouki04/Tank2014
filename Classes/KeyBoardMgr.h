#ifndef KeyBoardMgr_h__
#define KeyBoardMgr_h__

#include "cocoa\CCObject.h"

class KeyBoardMgr : public cocos2d::CCObject
{
public:
    KeyBoardMgr();
    ~KeyBoardMgr();

    bool isKeyDown(int virKey);
    bool isKeyUp(int virKey);

public:
    static KeyBoardMgr *sharedKeyBoardMgr();
    static void purgeSharedKeyBoardMgr();
};

#endif // KeyBoardMgr_h__
